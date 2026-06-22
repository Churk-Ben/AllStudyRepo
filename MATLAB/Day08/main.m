%% ============================================================
%  main.m
%  人像美颜主脚本：读取素材 -> 皮肤检测 -> 磨皮 -> 美白 -> 保存与可视化
%  运行前请确保同目录下存在 portrait.jpg
% ============================================================
clear; clc; close all;

% 始终从脚本所在目录读取素材，避免 MATLAB 当前工作目录不同而报错
scriptDir = fileparts(mfilename('fullpath'));
imgName   = fullfile(scriptDir, 'portrait2.jpeg');

% ---------- 读取与预处理 ----------
I = imread(imgName);
if size(I, 3) == 1
    I = repmat(I, [1 1 3]);
end
I = im2double(I);

% ---------- 可调参数 ----------
smoothStrength = 0.95;   % 磨皮强度 (0~1)
whitenStrength = 0.55;   % 美白强度 (0~1)

% ---------- 处理流程 ----------
[maskBinary, maskSoft] = detectSkinYCbCr(I);
smoothResult = smoothSkin(I, maskSoft, smoothStrength);
finalResult  = whitenSkinHSV(smoothResult, maskSoft, whitenStrength);

% ---------- 输出目录 ----------
outDir = fullfile(scriptDir, 'output_beauty');
if ~exist(outDir, 'dir')
    mkdir(outDir);
end

% ---------- 保存结果 ----------
imwrite(maskBinary, fullfile(outDir, '01_skin_mask_binary.png'));
imwrite(maskSoft,   fullfile(outDir, '02_skin_mask_soft.png'));
imwrite(smoothResult, fullfile(outDir, '03_smooth_result.png'));
imwrite(finalResult,  fullfile(outDir, '04_final_beauty.png'));
imwrite([I finalResult], fullfile(outDir, '05_compare_original_final.png'));

% ---------- 可视化 ----------
figure('Name', '人像美颜实验结果', 'Position', [200 150 900 500]);
subplot(2,3,1); imshow(I);            title('原图');
subplot(2,3,2); imshow(maskBinary);   title('皮肤检测掩膜');
subplot(2,3,3); imshow(maskSoft, []); title('羽化后的掩膜');
subplot(2,3,4); imshow(smoothResult); title('磨皮结果');
subplot(2,3,5); imshow(finalResult);  title('最终美颜结果');
subplot(2,3,6); imshow([I finalResult]); title('原图 / 最终结果');

disp(['处理完成，结果已保存到：' outDir]);