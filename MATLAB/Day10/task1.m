%% ============================================================
% 图像增强：自动陷波 + 频域平滑 + 轻空域去噪
%% ============================================================

clear; clc; close all;

%% 0. 读图
I_noisy = im2double(imread('dogDistorted.bmp'));
if ndims(I_noisy) == 3
    I_noisy = rgb2gray(I_noisy);
end

hasClean = false;
if exist('dogOriginal.bmp', 'file') == 2
    I_clean = im2double(imread('dogOriginal.bmp'));
    if ndims(I_clean) == 3
        I_clean = rgb2gray(I_clean);
    end
    hasClean = true;
end

%% 1. FFT
[rows, cols] = size(I_noisy);
crow = floor(rows / 2) + 1;
ccol = floor(cols / 2) + 1;

[X, Y] = meshgrid(1:cols, 1:rows);
D_center = sqrt((X - ccol).^2 + (Y - crow).^2);

F = fftshift(fft2(I_noisy));
S = log(1 + abs(F));

%% 2. 自动找周期噪声峰
S_bg = imgaussfilt(S, 18);
S_peak = mat2gray(S - S_bg);

% 不动低频中心，防止主体结构被当成噪声
S_peak(D_center < 25) = 0;

localMax = imregionalmax(S_peak);
idx = find(localMax);
[~, order] = sort(S_peak(idx), 'descend');

K = 30;          % 陷波点数量
D0 = 6;          % 陷波半径
minGain = 0.04; % 不完全挖空，减少振铃

K = min(K, numel(order));
idx = idx(order(1:K));
[rp, cp] = ind2sub(size(S_peak), idx);

%% 3. 构造高斯陷波器
H_notch = ones(rows, cols);

for k = 1:length(rp)
    r = rp(k);
    c = cp(k);

    D1 = (X - c).^2 + (Y - r).^2;
    notch1 = 1 - exp(-D1 / (2 * D0^2));

    r2 = 2 * crow - r;
    c2 = 2 * ccol - c;

    if r2 >= 1 && r2 <= rows && c2 >= 1 && c2 <= cols
        D2 = (X - c2).^2 + (Y - r2).^2;
        notch2 = 1 - exp(-D2 / (2 * D0^2));
        H_notch = H_notch .* notch1 .* notch2;
    else
        H_notch = H_notch .* notch1;
    end
end

H_notch = max(H_notch, minGain);
H_notch(D_center < 15) = 1;

%% 4. 频域温和低通平滑
% 这一步专门先压掉一部分高频随机噪点
cutoffRate = 0.15;     % 越小越平滑，越大越保细节
lpAlpha = 0.96;        % 低通参与强度，越大越平滑

cutoff = cutoffRate * min(rows, cols);
orderLP = 2;

H_low = 1 ./ (1 + (D_center ./ cutoff).^(2 * orderLP));

% 混合低通，不要直接强低通，避免发糊
H_smooth = (1 - lpAlpha) + lpAlpha * H_low;

% 总频域滤波器
H_total = H_notch .* H_smooth;
H_total(D_center < 12) = 1;

G = F .* H_total;

I_freq = real(ifft2(ifftshift(G)));
I_freq = clip01(I_freq);

%% 5. 空域处理：自适应保边平滑
% 思路：
% 平坦区域噪点明显，多用平滑结果；
% 边缘/细节区域容易被糊，更多保留 I_freq。

I_base = I_freq;

%% 5.1 先做一版温和去噪图
try
    I_wiener = wiener2(I_base, [3 3]);
catch
    I_wiener = I_base;
end
I_wiener = clip01(I_wiener);

try
    I_bilat = imbilatfilt(I_wiener, 0.035, 3);
catch
    I_bilat = imgaussfilt(I_wiener, 0.45);
end
I_bilat = clip01(I_bilat);

try
    I_smooth = imguidedfilter(I_bilat, I_base, ...
        'NeighborhoodSize', [5 5], ...
        'DegreeOfSmoothing', 0.00045);
catch
    I_smooth = I_bilat;
end
I_smooth = clip01(I_smooth);

%% 5.2 计算边缘/细节权重
[Gx, Gy] = imgradientxy(I_base, 'sobel');
G = sqrt(Gx.^2 + Gy.^2);
G = mat2gray(imgaussfilt(G, 0.8));

% W 越大，说明越平坦，越适合平滑
% W 越小，说明越像边缘，越应该保留原图
edgeT = 0.22;
W = 1 - min(G / edgeT, 1);
W = imgaussfilt(W, 1.0);

%% 5.3 自适应融合
% 平坦区域更多用 I_smooth，边缘区域更多用 I_base
smoothStrength = 0.78;

A = smoothStrength * W;
I_mix = A .* I_smooth + (1 - A) .* I_base;
I_mix = clip01(I_mix);

%% 5.4 只对边缘轻锐化，不对全图锐化
try
    I_sharp = imsharpen(I_mix, ...
        'Radius', 0.55, ...
        'Amount', 0.22, ...
        'Threshold', 0.035);
catch
    I_sharp = I_mix;
end

edgeWeight = 1 - W;
edgeWeight = 0.35 * edgeWeight;

I_final = edgeWeight .* I_sharp + (1 - edgeWeight) .* I_mix;
I_final = clip01(I_final);

%% 6. 显示
figure('Name', '图像增强结果', 'Color', [0.12 0.12 0.12]);

if hasClean
    subplot(2,3,1); imshow(I_clean, []); title('原始清晰');
else
    subplot(2,3,1); imshow(I_noisy, []); title('原图');
end

subplot(2,3,2); imshow(I_noisy, []); title('带噪声');

subplot(2,3,3); imshow(S, []); title('原始频谱');
hold on; plot(cp, rp, 'r+', 'MarkerSize', 6);

subplot(2,3,4); imshow(H_total, []); title('陷波 + 频域平滑');

subplot(2,3,5); imshow(I_freq, []); title('频域滤波后');

subplot(2,3,6); imshow(I_final, []); title('最终结果');

%% 7. 评价与保存
if hasClean
    fprintf('\n===== 评价 =====\n');
    fprintf('频域滤波后: MSE = %.4f, PSNR = %.4f dB, SSIM = %.4f\n', ...
        immse(I_freq, I_clean), psnr(I_freq, I_clean), ssim(I_freq, I_clean));

    fprintf('最终结果:   MSE = %.4f, PSNR = %.4f dB, SSIM = %.4f\n', ...
        immse(I_final, I_clean), psnr(I_final, I_clean), ssim(I_final, I_clean));
end

imwrite(I_freq, 'dog_freq_smooth.png');
imwrite(I_final, 'dog_final_result.png');

fprintf('\n已保存：dog_freq_smooth.png 和 dog_final_result.png\n');

%% 8. 工具函数
function I = clip01(I)
    I = min(max(I, 0), 1);
end