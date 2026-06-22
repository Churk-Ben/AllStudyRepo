% ============================================================
%  MAIN.M  —  美颜流水线主脚本
%  ============================================================
%  通过修改下方的 CONFIGURATION 区域组合不同算法,
%  运行脚本即可依次完成:
%    1. 加载图片    2. 皮肤掩膜    3. 五官/面颊定位
%    4. 磨皮        5. 美白        6. 唇色增强    7. 腮红
% ============================================================

clear; close all; clc;

% ---------- 确保脚本所在目录为工作目录 ----------
scriptDir = fileparts(mfilename('fullpath'));
if ~isempty(scriptDir)
    cd(scriptDir);
end
addpath(genpath(scriptDir));

% ======================== CONFIGURATION ========================

% -- 输入图片 (input/ 下的文件名) --
INPUT_IMAGE  = 'portrait4.jpg';

% -- 皮肤检测方法 --
%    1 = HSV 色彩空间 (detectSkin_1)
%    2 = YCbCr 色彩空间 (detectSkin_2)
SKIN_METHOD  = 2;

% -- 磨皮方法 --
%    1 = 引导滤波保边磨皮  (smoothSkin_1)
%    2 = 表面模糊细节磨皮  (smoothSkin_2)
%    3 = 双边滤波保边磨皮  (smoothSkin_3)
SMOOTH_METHOD = 1;

% -- 美白方法 --
%    1 = HSV 提亮 + 降饱和 (whitenSkin_1)
%    2 = Gamma 曲线美白    (whitenSkin_2)
WHITEN_METHOD = 2;

% -- 输出控制 --
SAVE_INTERMEDIATE = true;        % 是否保存每阶段结果
OUTPUT_DIR        = 'output';    % 输出目录

% ===============================================================

%% ==================== STEP 1: 加载图片 ====================
fprintf('\n========== STEP 1: Load Image ==========\n');
img = loadImage(INPUT_IMAGE);

if SAVE_INTERMEDIATE
    if ~exist(OUTPUT_DIR, 'dir'), mkdir(OUTPUT_DIR); end
    imwrite(img, fullfile(OUTPUT_DIR, 'step1_original.png'));
end

%% ==================== STEP 2: 皮肤掩膜 ====================
fprintf('\n========== STEP 2: Skin Mask ==========\n');
switch SKIN_METHOD
    case 1
        skinMask = detectSkin_1(img);
    case 2
        skinMask = detectSkin_2(img);
    otherwise
        error('Unknown SKIN_METHOD: %d', SKIN_METHOD);
end

if SAVE_INTERMEDIATE
    imwrite(skinMask, fullfile(OUTPUT_DIR, 'step2_skinMask.png'));
end

%% ==================== STEP 3: 五官 & 面颊定位 ====================
fprintf('\n========== STEP 3: Feature Detection ==========\n');
[lipMask, cheekMask] = detectFeatures_1(img, skinMask);

if SAVE_INTERMEDIATE
    imwrite(lipMask,   fullfile(OUTPUT_DIR, 'step3_lipMask.png'));
    imwrite(cheekMask, fullfile(OUTPUT_DIR, 'step3_cheekMask.png'));
end

%% ==================== STEP 4: 磨皮 ====================
fprintf('\n========== STEP 4: Skin Smoothing ==========\n');
switch SMOOTH_METHOD
    case 1
        img = smoothSkin_1(img, skinMask);
    case 2
        img = smoothSkin_2(img, skinMask);
    otherwise
        error('Unknown SMOOTH_METHOD: %d', SMOOTH_METHOD);
end

if SAVE_INTERMEDIATE
    imwrite(img, fullfile(OUTPUT_DIR, 'step4_smoothed.png'));
end

%% ==================== STEP 5: 美白 ====================
fprintf('\n========== STEP 5: Skin Whitening ==========\n');
switch WHITEN_METHOD
    case 1
        img = whitenSkin_1(img, skinMask);
    case 2
        img = whitenSkin_2(img, skinMask);
    otherwise
        error('Unknown WHITEN_METHOD: %d', WHITEN_METHOD);
end

if SAVE_INTERMEDIATE
    imwrite(img, fullfile(OUTPUT_DIR, 'step5_whitened.png'));
end

%% ==================== STEP 6: 唇部增强 ====================
fprintf('\n========== STEP 6: Lip Enhancement ==========\n');
img = enhanceLip_1(img, lipMask);

if SAVE_INTERMEDIATE
    imwrite(img, fullfile(OUTPUT_DIR, 'step6_lipEnhanced.png'));
end

%% ==================== STEP 7: 腮红 ====================
fprintf('\n========== STEP 7: Blush ==========\n');
img = applyBlush_1(img, cheekMask);

if SAVE_INTERMEDIATE
    imwrite(img, fullfile(OUTPUT_DIR, 'step7_final.png'));
end

%% ==================== 完成 ====================
fprintf('\n========== Pipeline Complete ==========\n');
fprintf('Final result saved to: %s\n', fullfile(OUTPUT_DIR, 'step7_final.png'));

% 展示最终效果
figure('Name', 'Beauty Pipeline Result', 'NumberTitle', 'off');
imshow(img);
title(sprintf('Final (Skin=%d | Smooth=%d | Whiten=%d)', ...
      SKIN_METHOD, SMOOTH_METHOD, WHITEN_METHOD));
