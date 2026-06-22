clear; clc; close all;

scriptDir = fileparts(mfilename('fullpath'));
imgPath = fullfile(scriptDir, 'portrait.jpg');
if ~exist(imgPath, 'file')
    imgPath = fullfile(scriptDir, '人像美颜素材1.jpeg');
end
if ~exist(imgPath, 'file')
    error('未找到人像图片，请将 portrait.jpg 放到当前目录。');
end

outDir = fullfile(scriptDir, 'output_beauty');
if ~exist(outDir, 'dir')
    mkdir(outDir);
end

I = im2double(imread(imgPath));
if size(I, 3) == 1
    I = repmat(I, [1 1 3]);
end

naturalSmooth = 0.40;
naturalWhiten = 0.20;
strongSmooth = 0.65;
strongWhiten = 0.35;

%% 皮肤检测和基础美颜流程
rgbMaskRaw = detectSkinRGB(I);
hsvMaskRaw = detectSkinHSV(I);
ycbcrMaskRaw = detectSkinYCbCr(I);

[rgbMask, ~] = processSkinMask(rgbMaskRaw, I);
[hsvMask, ~] = processSkinMask(hsvMaskRaw, I);
[maskBinary, maskSoft] = processSkinMask(ycbcrMaskRaw, I);

[smoothResult, finalResult] = runBeautyPipeline( ...
    I, maskSoft, strongSmooth, strongWhiten);

imwrite(I, fullfile(outDir, '01_original.png'));
imwrite(maskBinary, fullfile(outDir, '02_skin_mask_ycbcr.png'));
imwrite(maskSoft, fullfile(outDir, '03_skin_mask_soft.png'));
imwrite(smoothResult, fullfile(outDir, '04_smooth_result.png'));
imwrite(finalResult, fullfile(outDir, '05_final_beauty.png'));
imwrite([I finalResult], fullfile(outDir, '06_original_final_compare.png'));
imwrite(rgbMask, fullfile(outDir, 'RGB_skin_mask.png'));
imwrite(hsvMask, fullfile(outDir, 'HSV_skin_mask.png'));
imwrite(maskBinary, fullfile(outDir, 'YCbCr_skin_mask.png'));

saveCompareFigure( ...
    {I, maskBinary, maskSoft, smoothResult, finalResult, [I finalResult]}, ...
    {'原图', 'YCbCr皮肤掩膜', '羽化掩膜', '磨皮结果', ...
     '最终美颜', '原图 / 最终结果'}, [2 3], ...
    fullfile(outDir, 'basic_beauty_process.png'), '基础美颜流程', true);

saveCompareFigure({I, rgbMask, hsvMask, maskBinary}, ...
    {'原图', 'RGB阈值', 'HSV阈值', 'YCbCr阈值'}, [2 2], ...
    fullfile(outDir, '07_skin_detection_compare.png'), ...
    '皮肤检测算法对比', true);
disp('皮肤检测对比完成。');

%% 磨皮方法对比
gaussianResult = gaussianSmoothSkin(I, maskSoft, strongSmooth);
medianResult = medianSmoothSkin(I, maskSoft, strongSmooth);
[bilateralResult, bilateralSupported] = ...
    bilateralSmoothSkin(I, maskSoft, strongSmooth);
[guidedResult, guidedSupported] = ...
    guidedSmoothSkin(I, maskSoft, strongSmooth);

imwrite(gaussianResult, fullfile(outDir, 'gaussian_smooth.png'));
imwrite(medianResult, fullfile(outDir, 'median_smooth.png'));
imwrite(bilateralResult, fullfile(outDir, 'bilateral_smooth.png'));
imwrite(guidedResult, fullfile(outDir, 'guided_smooth.png'));

saveCompareFigure( ...
    {I, gaussianResult, medianResult, bilateralResult, guidedResult}, ...
    {'原图', '高斯滤波', '中值滤波', '双边滤波', '引导滤波'}, [2 3], ...
    fullfile(outDir, '08_smooth_method_compare.png'), ...
    '磨皮算法对比', true);
disp('磨皮算法对比完成。');

if ~bilateralSupported
    disp('当前 MATLAB 不支持 imbilatfilt，双边滤波使用高斯近似。');
end
if ~guidedSupported
    disp('当前 MATLAB 不支持 imguidedfilter，引导滤波使用高斯近似。');
end

%% 美颜模式和唇色增强
[~, naturalBeauty] = runBeautyPipeline( ...
    I, maskSoft, naturalSmooth, naturalWhiten);
[~, strongBeauty] = runBeautyPipeline( ...
    I, maskSoft, strongSmooth, strongWhiten);
[lipResult, lipMask] = enhanceLipColor(strongBeauty);

imwrite(naturalBeauty, fullfile(outDir, 'natural_beauty.png'));
imwrite(strongBeauty, fullfile(outDir, 'strong_beauty.png'));
imwrite(lipMask, fullfile(outDir, 'lip_mask.png'));
imwrite(lipResult, fullfile(outDir, 'lip_enhance_result.png'));

saveCompareFigure({I, naturalBeauty, strongBeauty}, ...
    {'原图', '自然美颜', '强美颜'}, [1 3], ...
    fullfile(outDir, '09_beauty_mode_compare.png'), ...
    '美颜强度对比', false);

saveCompareFigure({strongBeauty, lipResult}, ...
    {'基础美颜', '唇色增强'}, [1 2], ...
    fullfile(outDir, '10_lip_enhancement_compare.png'), ...
    '唇色增强对比', false);

saveCompareFigure( ...
    {I, naturalBeauty, strongBeauty, finalResult, lipResult}, ...
    {'原图', '自然美颜', '强美颜', '基础美颜', '唇色增强'}, [2 3], ...
    fullfile(outDir, 'beauty_extension_overview.png'), ...
    '美颜模式与美妆扩展', true);

disp('美颜模式和唇色增强完成。');
disp(['全部结果已保存到：' outDir]);
