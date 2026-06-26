%% ============================================================
%  用清晰图频谱作为参考：频域幅值匹配 + 轻空域处理
%  输入：dogOriginal.bmp / dogDistorted.bmp
%% ============================================================

clear; clc; close all;

%% 1. 读图
I_clean = im2double(imread('dogOriginal.bmp'));
I_noisy = im2double(imread('dogDistorted.bmp'));

if ndims(I_clean) == 3, I_clean = rgb2gray(I_clean); end
if ndims(I_noisy) == 3, I_noisy = rgb2gray(I_noisy); end

[rows, cols] = size(I_noisy);
crow = floor(rows / 2) + 1;
ccol = floor(cols / 2) + 1;

[X, Y] = meshgrid(1:cols, 1:rows);
D_center = sqrt((X - ccol).^2 + (Y - crow).^2);

%% 2. FFT
F_clean = fftshift(fft2(I_clean));
F_noisy = fftshift(fft2(I_noisy));

Mag_clean = abs(F_clean);
Mag_noisy = abs(F_noisy);
Phase_noisy = angle(F_noisy);

Log_clean = log(1 + Mag_clean);
Log_noisy = log(1 + Mag_noisy);

%% 3. 用清晰图频谱的"径向包络"作为参考，不逐点硬匹配

Log_clean_s = imgaussfilt(Log_clean, 1.2);
Log_noisy_s = imgaussfilt(Log_noisy, 0.8);

R = round(D_center);
maxR = max(R(:));

cleanRad = zeros(maxR + 1, 1);
noisyRad = zeros(maxR + 1, 1);

for rr = 0:maxR
    mask = (R == rr);
    cleanRad(rr + 1) = median(Log_clean_s(mask));
    noisyRad(rr + 1) = median(Log_noisy_s(mask));
end

% 平滑径向曲线，防止一圈一圈跳变
cleanRad = smoothdata(cleanRad, 'gaussian', 21);
noisyRad = smoothdata(noisyRad, 'gaussian', 21);

% 映射回二维频域
CleanEnv = cleanRad(R + 1);
NoisyEnv = noisyRad(R + 1);

% 只压制"带噪图该半径能量明显高于清晰图"的部分
margin = 0.08;
refStrength = 0.75;
minGain = 0.18;

excess = max(0, NoisyEnv - CleanEnv - margin);
H_ref = exp(-refStrength * excess);

H_ref = max(H_ref, minGain);
H_ref(D_center < 18) = 1;

%% 4. 再单独压明显周期峰
DiffSpec = Log_noisy - Log_clean;
DiffSpec = mat2gray(DiffSpec);
DiffSpec(D_center < 25) = 0;

localMax = imregionalmax(DiffSpec);
idx = find(localMax);
[~, order] = sort(DiffSpec(idx), 'descend');

K = 40;          % 周期峰数量
D0 = 5;          % 周期峰压制半径
peakGain = 0.1; % 峰值处最低保留

K = min(K, numel(order));
idx = idx(order(1:K));
[rp, cp] = ind2sub(size(DiffSpec), idx);

H_peak = ones(rows, cols);

for k = 1:length(rp)
    r = rp(k);
    c = cp(k);

    D1 = (X - c).^2 + (Y - r).^2;
    notch1 = 1 - (1 - peakGain) * exp(-D1 / (2 * D0^2));

    r2 = 2 * crow - r;
    c2 = 2 * ccol - c;

    if r2 >= 1 && r2 <= rows && c2 >= 1 && c2 <= cols
        D2 = (X - c2).^2 + (Y - r2).^2;
        notch2 = 1 - (1 - peakGain) * exp(-D2 / (2 * D0^2));
        H_peak = H_peak .* notch1 .* notch2;
    else
        H_peak = H_peak .* notch1;
    end
end

H_peak(D_center < 18) = 1;

%% 5. 频域重建
H_total = H_ref .* H_peak;
H_total(D_center < 18) = 1;

Mag_new = Mag_noisy .* H_total;
F_new = Mag_new .* exp(1i * Phase_noisy);

I_freq = real(ifft2(ifftshift(F_new)));
I_freq = clip01(I_freq);

%% 6. 轻空域处理
% 不要重度平滑，只压残余颗粒
try
    I_wiener = wiener2(I_freq, [3 3]);
catch
    I_wiener = I_freq;
end
I_wiener = clip01(I_wiener);

try
    I_bilat = imbilatfilt(I_wiener, 0.028, 3);
catch
    I_bilat = imgaussfilt(I_wiener, 0.35);
end
I_bilat = clip01(I_bilat);

% 混合，避免右图那种过糊
mixRate = 0.60;
I_final = mixRate * I_bilat + (1 - mixRate) * I_freq;

try
    I_final = imsharpen(I_final, ...
        'Radius', 0.5, ...
        'Amount', 0.22, ...
        'Threshold', 0.035);
catch
end

I_final = clip01(I_final);

%% 直方图轻度增强：保护亮部
I_before_contrast = I_final;

lowHigh = stretchlim(I_before_contrast, [0.015 0.995]);

I_contrast = imadjust(I_before_contrast, lowHigh, [0 1], 1.08);

contrastStrength = 0.40;

I_final = (1 - contrastStrength) * I_before_contrast + ...
           contrastStrength  * I_contrast;

I_final = min(max(I_final, 0), 1);

%% 最后一步：导向滤波版，轻去噪不明显柔化
I_before = I_final;

I_guided = imguidedfilter(I_before, I_before, ...
    'NeighborhoodSize', [5 5], ...
    'DegreeOfSmoothing', 0.00045);

I_guided = min(max(I_guided, 0), 1);

guidedStrength = 0.65;

I_final = guidedStrength * I_guided + ...
          (1 - guidedStrength) * I_before;

I_final = min(max(I_final, 0), 1);

%% 最后一步：压灰感 / 压曝光 / 拉回黑位
I_before_tone = I_final;

% 手动调色参数
blackPoint = 0.12;     % 压暗部，越大暗部越黑
whitePoint = 0.95;     % 保持亮部，不要太低，否则白毛会爆
gammaVal = 1.55;       % >1 会压暗中间调，灰感会下降

I_tone = imadjust(I_before_tone, ...
    [blackPoint whitePoint], ...
    [0 1], ...
    gammaVal);

% 混合，避免一下子调太猛
toneStrength = 0.85;

I_final = (1 - toneStrength) * I_before_tone + ...
           toneStrength  * I_tone;

I_final = min(max(I_final, 0), 1);

%% 7. 显示
figure('Name', '频域参考清晰图增强', 'Color', [0.12 0.12 0.12]);

subplot(2,4,1); imshow(I_clean, []); title('原始清晰');
subplot(2,4,2); imshow(I_noisy, []); title('带噪声');
subplot(2,4,3); imshow(Log_clean, []); title('清晰图频谱');
subplot(2,4,4); imshow(Log_noisy, []); title('带噪图频谱');

subplot(2,4,5); imshow(H_ref, []); title('清晰频谱参考压制');
subplot(2,4,6); imshow(H_peak, []); title('周期峰压制');
subplot(2,4,7); imshow(I_freq, []); title('频域重建');
subplot(2,4,8); imshow(I_final, []); title('最终结果');

%% 8. 评价
fprintf('\n===== 评价 =====\n');
fprintf('频域重建: MSE = %.4f, PSNR = %.4f dB, SSIM = %.4f\n', ...
    immse(I_freq, I_clean), psnr(I_freq, I_clean), ssim(I_freq, I_clean));

fprintf('最终结果: MSE = %.4f, PSNR = %.4f dB, SSIM = %.4f\n', ...
    immse(I_final, I_clean), psnr(I_final, I_clean), ssim(I_final, I_clean));

imwrite(I_freq, 'dog_ref_freq.png');
imwrite(I_final, 'dog_ref_final.png');

%% 9. 工具函数
function I = clip01(I)
    I = min(max(I, 0), 1);
end