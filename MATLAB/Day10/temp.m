%% ============================================================
%  观察清晰图频域特征
%  输入：dogOriginal.bmp
%  可选：dogDistorted.bmp
%% ============================================================

clear; clc; close all;

%% 1. 读取清晰图
I_clean = im2double(imread('dogOriginal.bmp'));

if ndims(I_clean) == 3
    I_clean = rgb2gray(I_clean);
end

%% 2. 计算清晰图 FFT
F_clean = fftshift(fft2(I_clean));

Mag_clean = abs(F_clean);
LogMag_clean = log(1 + Mag_clean);
Phase_clean = angle(F_clean);

% 频谱增强显示，避免中心低频太亮导致其他细节看不见
LogMag_clean_enh = enhance_spectrum(LogMag_clean);

%% 3. 显示清晰图频谱
figure('Name', '清晰图频域观察', 'Color', [0.12 0.12 0.12]);

subplot(2,2,1);
imshow(I_clean, []);
title('原始清晰图');

subplot(2,2,2);
imshow(LogMag_clean, []);
title('清晰图频谱 log(1 + |F|)');

subplot(2,2,3);
imshow(LogMag_clean_enh, []);
title('清晰图频谱增强显示');

subplot(2,2,4);
imshow(Phase_clean, []);
title('清晰图相位谱');

%% 4. 如果存在带噪图，做频谱对比
if exist('dogDistorted.bmp', 'file') == 2

    I_noisy = im2double(imread('dogDistorted.bmp'));

    if ndims(I_noisy) == 3
        I_noisy = rgb2gray(I_noisy);
    end

    F_noisy = fftshift(fft2(I_noisy));

    LogMag_noisy = log(1 + abs(F_noisy));
    LogMag_noisy_enh = enhance_spectrum(LogMag_noisy);

    figure('Name', '清晰图与带噪图频谱对比', 'Color', [0.12 0.12 0.12]);

    subplot(2,3,1);
    imshow(I_clean, []);
    title('原始清晰图');

    subplot(2,3,2);
    imshow(LogMag_clean, []);
    title('清晰图频谱');

    subplot(2,3,3);
    imshow(LogMag_clean_enh, []);
    title('清晰图频谱增强');

    subplot(2,3,4);
    imshow(I_noisy, []);
    title('带噪声图');

    subplot(2,3,5);
    imshow(LogMag_noisy, []);
    title('带噪图频谱');

    subplot(2,3,6);
    imshow(LogMag_noisy_enh, []);
    title('带噪图频谱增强');

end

%% 5. 保存频谱图，方便放大观察
imwrite(mat2gray(LogMag_clean), 'clean_spectrum_log.png');
imwrite(LogMag_clean_enh, 'clean_spectrum_enhanced.png');

fprintf('已保存：clean_spectrum_log.png\n');
fprintf('已保存：clean_spectrum_enhanced.png\n');

%% ============================================================
%  局部函数：增强频谱显示
%% ============================================================

function S_out = enhance_spectrum(S)

    S = mat2gray(S);

    % 压掉过亮中心，让周围频率细节更容易看见
    sortedVals = sort(S(:));
    highIdx = round(0.995 * numel(sortedVals));
    highVal = sortedVals(highIdx);

    S_clip = min(S, highVal);
    S_clip = mat2gray(S_clip);

    % gamma 增强，让弱频率点更明显
    gamma = 0.55;
    S_out = S_clip .^ gamma;

end