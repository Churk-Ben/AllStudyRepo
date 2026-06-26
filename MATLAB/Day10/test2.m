%% ============================================================
%  近盲图像去噪：径向频谱压制 + 周期峰陷波 + 轻后处理
%  dogDistorted.bmp 必需；dogOriginal.bmp 仅用于弱参考和评价
%% ============================================================

clear; clc; close all;

%% 1. 读图
I_noisy = im2double(imread('dogDistorted.bmp'));
if ndims(I_noisy) == 3, I_noisy = rgb2gray(I_noisy); end

hasClean = exist('dogOriginal.bmp', 'file') == 2;
if hasClean
    I_clean = im2double(imread('dogOriginal.bmp'));
    if ndims(I_clean) == 3, I_clean = rgb2gray(I_clean); end
end

[rows, cols] = size(I_noisy);
crow = floor(rows / 2) + 1;
ccol = floor(cols / 2) + 1;
[X, Y] = meshgrid(1:cols, 1:rows);
D = sqrt((X - ccol).^2 + (Y - crow).^2);
R = round(D);
maxR = max(R(:));

%% 2. 参数区
% refMix = 0 表示严格盲去噪；
% refMix 越大，越依赖清晰图频谱。建议 0 ~ 0.20。
refMix = 0;

% 负值表示压暗清晰参考包络，让它不再像"答案模板"
refDark = 0;

% 盲估计时，对高频径向包络额外压暗
blindDrop = 0.1;

% 径向压制强度
margin = 0.06;
refStrength = 0.90;
minGain = 0.16;

% 周期峰陷波参数
K = 42;
D0 = 5;
peakGain = 0.12;

%% 3. FFT
F_noisy = fftshift(fft2(I_noisy));
Mag_noisy = abs(F_noisy);
Phase_noisy = angle(F_noisy);
Log_noisy = log(1 + Mag_noisy);

Log_noisy_s = imgaussfilt(Log_noisy, 0.8);
noisyRad = radial_median(Log_noisy_s, R, maxR);
noisyRad = smoothdata(noisyRad, 'gaussian', 21);

%% 4. 构造近盲径向参考包络
rho = (0:maxR)' / maxR;

% 盲参考：从带噪图自身估计，再压低高频
blindRad = noisyRad - blindDrop * rho.^1.15;

if hasClean && refMix > 0
    F_clean = fftshift(fft2(I_clean));
    Log_clean = log(1 + abs(F_clean));
    Log_clean_s = imgaussfilt(Log_clean, 1.2);

    cleanRad = radial_median(Log_clean_s, R, maxR);
    cleanRad = smoothdata(cleanRad, 'gaussian', 21);

    % 弱参考：只混入一小部分清晰图径向包络
    targetRad = (1 - refMix) * blindRad + ...
                 refMix  * (cleanRad + refDark);
else
    targetRad = blindRad;
end

NoisyEnv = noisyRad(R + 1);
TargetEnv = targetRad(R + 1);

excess = max(0, NoisyEnv - TargetEnv - margin);
H_rad = exp(-refStrength * excess);
H_rad = max(H_rad, minGain);
H_rad(D < 18) = 1;

%% 5. 盲检测周期峰并陷波
% 不再用 Log_noisy - Log_clean，而是用带噪频谱自身的局部异常峰
SpecBg = imgaussfilt(Log_noisy, 12);
PeakScore = Log_noisy - SpecBg;
PeakScore = mat2gray(PeakScore);
PeakScore(D < 25) = 0;

% 只保留明显高于径向背景的峰
PeakScore(Log_noisy < NoisyEnv + 0.08) = 0;

localMax = imregionalmax(PeakScore);
idx = find(localMax);
[~, order] = sort(PeakScore(idx), 'descend');

K = min(K, numel(order));
idx = idx(order(1:K));
[rp, cp] = ind2sub(size(PeakScore), idx);

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

H_peak(D < 18) = 1;

%% 6. 频域重建
H_total = H_rad .* H_peak;
H_total(D < 18) = 1;

F_new = Mag_noisy .* H_total .* exp(1i * Phase_noisy);
I_freq = real(ifft2(ifftshift(F_new)));
I_freq = clip01(I_freq);

%% 7. 轻空域后处理
try
    I_wiener = wiener2(I_freq, [3 3]);
catch
    I_wiener = I_freq;
end
I_wiener = clip01(I_wiener);

try
    I_bilat = imbilatfilt(I_wiener, 0.026, 2.6);
catch
    I_bilat = imguidedfilter(I_wiener, I_wiener, ...
        'NeighborhoodSize', [5 5], ...
        'DegreeOfSmoothing', 0.00045);
end
I_bilat = clip01(I_bilat);

I_final = 0.58 * I_bilat + 0.42 * I_freq;
I_final = clip01(I_final);

try
    I_guided = imguidedfilter(I_final, I_freq, ...
        'NeighborhoodSize', [5 5], ...
        'DegreeOfSmoothing', 0.00045);
    I_final = 0.60 * I_guided + 0.40 * I_final;
catch
end
I_final = clip01(I_final);

%% 8. 灰度动态范围调整
lowHigh = stretchlim(I_final, [0.015 0.995]);
I_contrast = imadjust(I_final, lowHigh, [0 1], 1.08);
I_final = 0.35 * I_contrast + 0.65 * I_final;
I_final = clip01(I_final);

I_tone = imadjust(I_final, [0.10 0.96], [0 1], 1.35);
I_final = 0.55 * I_tone + 0.45 * I_final;
I_final = clip01(I_final);

%% 9. 显示
figure('Name', '近盲频域去噪', 'Color', [0.12 0.12 0.12]);

if hasClean
    subplot(2,4,1); imshow(I_clean, []); title('原始清晰');
else
    subplot(2,4,1); imshow(I_noisy, []); title('输入图');
end

subplot(2,4,2); imshow(I_noisy, []); title('带噪声');
subplot(2,4,3); imshow(Log_noisy, []); title('带噪频谱');
subplot(2,4,4); imshow(PeakScore, []); title('盲检测周期峰');

subplot(2,4,5); imshow(H_rad, []); title('径向参考压制');
subplot(2,4,6); imshow(H_peak, []); title('周期峰陷波');
subplot(2,4,7); imshow(I_freq, []); title('频域重建');
subplot(2,4,8); imshow(I_final, []); title('最终结果');

%% 10. 评价
if hasClean
    fprintf('\n===== 评价 =====\n');
    fprintf('refMix = %.2f, refDark = %.3f, blindDrop = %.3f\n', ...
        refMix, refDark, blindDrop);

    fprintf('频域重建: MSE = %.4f, PSNR = %.4f dB, SSIM = %.4f\n', ...
        immse(I_freq, I_clean), psnr(I_freq, I_clean), ssim(I_freq, I_clean));

    fprintf('最终结果: MSE = %.4f, PSNR = %.4f dB, SSIM = %.4f\n', ...
        immse(I_final, I_clean), psnr(I_final, I_clean), ssim(I_final, I_clean));
end

imwrite(I_freq, 'dog_nearblind_freq.png');
imwrite(I_final, 'dog_nearblind_final.png');

%% 11. 工具函数
function rad = radial_median(S, R, maxR)
    rad = zeros(maxR + 1, 1);
    for rr = 0:maxR
        vals = S(R == rr);
        rad(rr + 1) = median(vals(:));
    end
end

function I = clip01(I)
    I = min(max(I, 0), 1);
end