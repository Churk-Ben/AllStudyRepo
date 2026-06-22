clear; clc; close all;

scriptDir = fileparts(mfilename('fullpath'));
imgPath = fullfile(scriptDir, 'portrait.jpg');
if ~exist(imgPath, 'file')
    error('未找到 portrait.jpg，请将人像图片放到当前目录，并命名为 portrait.jpg。');
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

%% 基础流程与皮肤检测对比
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

fig1 = saveCompareFigure( ...
    {I, maskBinary, maskSoft, smoothResult, finalResult, [I finalResult]}, ...
    {'原图', 'YCbCr皮肤掩膜', '羽化掩膜', '磨皮结果', ...
     '最终美颜', '原图 / 最终结果'}, [2 3], ...
    fullfile(outDir, 'basic_beauty_process.png'), '基础美颜流程', true);

fig2 = saveCompareFigure( ...
    {I, rgbMask, hsvMask, maskBinary}, ...
    {'原图', 'RGB阈值', 'HSV阈值', 'YCbCr阈值'}, [2 2], ...
    fullfile(outDir, '07_skin_detection_compare.png'), ...
    '皮肤检测算法对比', true);
disp('皮肤检测对比完成：已生成 RGB、HSV、YCbCr 掩膜及 07_skin_detection_compare.png');

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

fig3 = saveCompareFigure( ...
    {I, gaussianResult, medianResult, bilateralResult, guidedResult}, ...
    {'原图', '高斯滤波', '中值滤波', '双边滤波', '引导滤波'}, [2 3], ...
    fullfile(outDir, '08_smooth_method_compare.png'), ...
    '磨皮算法对比', true);
disp('磨皮算法对比完成：已生成四种磨皮结果及 08_smooth_method_compare.png');
if ~bilateralSupported
    disp('当前 MATLAB 不支持 imbilatfilt，双边滤波结果使用高斯滤波近似。');
end
if ~guidedSupported
    disp('当前 MATLAB 不支持 imguidedfilter，引导滤波结果使用高斯滤波近似。');
end

%% 自然美颜、强美颜与唇色增强
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

fig4 = saveCompareFigure( ...
    {I, naturalBeauty, strongBeauty, finalResult, lipResult}, ...
    {'原图', '自然美颜', '强美颜', '基础美颜', '唇色增强'}, [2 3], ...
    fullfile(outDir, 'beauty_extension_overview.png'), ...
    '美颜模式与美妆扩展', true);
disp('美颜模式与唇色增强完成：已生成 09、10 对比图及唇色掩膜。');

drawnow;
disp(' ');
disp(['全部处理完成，结果目录：' outDir]);
disp('已生成基础流程图、三种肤色检测、四种磨皮方法、两种美颜模式和唇色增强结果。');


function mask = detectSkinRGB(I)
R = I(:,:,1); G = I(:,:,2); B = I(:,:,3);
channelMax = max(I, [], 3);
channelMin = min(I, [], 3);
mask = R > 95/255 & G > 40/255 & B > 20/255 & ...
       R > G & R > B & abs(R-G) > 15/255 & ...
       channelMax-channelMin > 15/255;
end


function mask = detectSkinHSV(I)
hsvImg = rgb2hsv(I);
H = hsvImg(:,:,1); S = hsvImg(:,:,2); V = hsvImg(:,:,3);
redHue = H <= 0.12 | H >= 0.96;
mask = redHue & S >= 0.15 & S <= 0.75 & V >= 0.25;
end


function mask = detectSkinYCbCr(I)
ycbcr = rgb2ycbcr(I);
Y = ycbcr(:,:,1); Cb = ycbcr(:,:,2); Cr = ycbcr(:,:,3);
mask = Cb >= 77/255 & Cb <= 127/255 & ...
       Cr >= 133/255 & Cr <= 173/255 & ...
       Y > 40/255 & Y < 245/255;
end


function [mask, maskSoft] = processSkinMask(mask, I)
mask = logical(mask);
mask = imopen(mask, makeDisk(1));
mask = imclose(mask, makeDisk(3));

% 仅填充小孔，保留眼睛和嘴部等较大的非皮肤区域。
holes = imfill(mask, 'holes') & ~mask;
smallHoles = holes & ~bwareaopen(holes, 350);
mask = mask | smallHoles;
mask = bwareaopen(mask, 80);

maskSoft = imgaussfilt(double(mask), 4);
ycbcr = rgb2ycbcr(I);
Y = ycbcr(:,:,1);
S = rgb2hsv(I); S = S(:,:,2);
lightWeight = min(max((Y-0.10)/0.18, 0), 1);
satProtection = 1 - 0.70*min(max((S-0.48)/0.30, 0), 1);
maskSoft = maskSoft .* lightWeight .* satProtection;
maskSoft = max(0, min(1, maskSoft));
end


function [smoothResult, finalResult] = runBeautyPipeline( ...
    I, maskSoft, smoothStrength, whitenStrength)
smoothResult = smoothSkin(I, maskSoft, smoothStrength);
finalResult = whitenSkinHSV(smoothResult, maskSoft, whitenStrength);
end


function result = smoothSkin(I, maskSoft, strength)
[bilateralResult, supported] = bilateralSmoothSkin(I, maskSoft, strength);
gaussianResult = gaussianSmoothSkin(I, maskSoft, strength);
if supported
    result = 0.80*bilateralResult + 0.20*gaussianResult;
else
    result = gaussianResult;
end
result = max(0, min(1, result));
end


function result = gaussianSmoothSkin(I, maskSoft, strength)
filtered = zeros(size(I));
sigma = 1.2 + 2.3*strength;
for c = 1:3
    filtered(:,:,c) = imgaussfilt(I(:,:,c), sigma);
end
result = blendByMask(I, filtered, maskSoft, strength);
end


function result = medianSmoothSkin(I, maskSoft, strength)
filtered = zeros(size(I));
kernelSize = 3 + 2*(strength > 0.55);
for c = 1:3
    filtered(:,:,c) = medfilt2(I(:,:,c), ...
        [kernelSize kernelSize], 'symmetric');
end
result = blendByMask(I, filtered, maskSoft, strength);
end


function [result, supported] = bilateralSmoothSkin(I, maskSoft, strength)
supported = exist('imbilatfilt', 'file') == 2;
if ~supported
    result = gaussianSmoothSkin(I, maskSoft, strength);
    return;
end
filtered = zeros(size(I));
degree = 0.025 + 0.045*strength;
spatialSigma = 5 + 8*strength;
for c = 1:3
    filtered(:,:,c) = imbilatfilt(I(:,:,c), degree, spatialSigma);
end
result = blendByMask(I, filtered, maskSoft, strength);
end


function [result, supported] = guidedSmoothSkin(I, maskSoft, strength)
supported = exist('imguidedfilter', 'file') == 2;
if ~supported
    result = gaussianSmoothSkin(I, maskSoft, strength);
    return;
end
filtered = zeros(size(I));
windowSize = 5 + 2*round(3*strength);
if mod(windowSize, 2) == 0
    windowSize = windowSize + 1;
end
for c = 1:3
    filtered(:,:,c) = imguidedfilter(I(:,:,c), ...
        'NeighborhoodSize', [windowSize windowSize], ...
        'DegreeOfSmoothing', 0.0005 + 0.003*strength);
end
result = blendByMask(I, filtered, maskSoft, strength);
end


function result = whitenSkinHSV(I, maskSoft, strength)
hsvImg = rgb2hsv(I);
H = hsvImg(:,:,1); S = hsvImg(:,:,2); V = hsvImg(:,:,3);
S2 = max(0, min(1, S.*(1-0.18*strength)));
V2 = max(0, min(1, V.*(1+0.25*strength)+0.03*strength));
whiteImg = hsv2rgb(cat(3, H, S2, V2));
result = blendByMask(I, whiteImg, maskSoft, 1.0);
end


function result = blendByMask(I, filtered, maskSoft, strength)
alpha = repmat(max(0, min(1, maskSoft*strength)), [1 1 3]);
result = I.*(1-alpha) + filtered.*alpha;
result = max(0, min(1, result));
end


function [result, lipMaskSoft] = enhanceLipColor(I)
[height, width, ~] = size(I);
hsvImg = rgb2hsv(I);
H = hsvImg(:,:,1); S = hsvImg(:,:,2); V = hsvImg(:,:,3);
R = I(:,:,1); G = I(:,:,2); B = I(:,:,3);

roi = false(height, width);
rowRange = round(0.46*height):round(0.60*height);
colRange = round(0.40*width):round(0.68*width);
roi(rowRange, colRange) = true;
redHue = H <= 0.08 | H >= 0.94;
redness = R - 0.5*(G+B);
lipMask = roi & redHue & S >= 0.30 & V >= 0.18 & ...
          redness >= 0.25 & R > 1.15*G & R > 1.12*B;
lipMask = imopen(lipMask, makeDisk(1));
lipMask = imclose(lipMask, makeDisk(2));
lipMask = bwareaopen(lipMask, 15);
if any(lipMask(:))
    lipMask = bwareafilt(lipMask, 1);
end
lipMaskSoft = imgaussfilt(double(lipMask), 2.0);
lipMaskSoft = max(0, min(1, lipMaskSoft));

H2 = H;
lowRed = H <= 0.12;
H2(lowRed) = 0.65*H(lowRed);
highRed = H >= 0.92;
H2(highRed) = 1 - 0.65*(1-H(highRed));
S2 = min(1, S*1.30);
V2 = min(1, V*1.03);
colored = hsv2rgb(cat(3, H2, S2, V2));
result = blendByMask(I, colored, lipMaskSoft, 0.75);
end


function fig = saveCompareFigure(images, titles, layoutSize, ...
    outPath, figureName, visible)
% 批处理模式没有桌面图窗；交互运行时正常显示指定窗口。
showWindow = visible && usejava('desktop');
if showWindow
    visibility = 'on';
else
    visibility = 'off';
end
fig = figure('Name', figureName, 'Color', 'w', 'Visible', visibility, ...
    'Position', [80 80 1200 720]);
tiledlayout(layoutSize(1), layoutSize(2), ...
    'TileSpacing', 'compact', 'Padding', 'compact');
for k = 1:numel(images)
    nexttile;
    if ndims(images{k}) == 2
        imshow(images{k}, []);
    else
        imshow(images{k});
    end
    title(titles{k});
end
drawnow;
exportgraphics(fig, outPath, 'Resolution', 160);
if ~showWindow
    close(fig);
end
end


function se = makeDisk(r)
try
    se = strel('disk', r);
catch
    se = strel('disk', r, 0);
end
end
