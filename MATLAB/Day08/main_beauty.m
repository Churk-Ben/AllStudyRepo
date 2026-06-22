clear; clc; close all;

% 始终从脚本所在目录读取素材，避免 MATLAB 当前工作目录不同而报错。
scriptDir = fileparts(mfilename('fullpath'));
imgName = fullfile(scriptDir, 'portrait.jpg');

I = imread(imgName);
if size(I, 3) == 1
    I = repmat(I, [1 1 3]);
end
I = im2double(I);

smoothStrength = 0.65;
whitenStrength = 0.35;

[maskBinary, maskSoft] = detectSkinYCbCr(I);
smoothResult = smoothSkin(I, maskSoft, smoothStrength);
finalResult = whitenSkinHSV(smoothResult, maskSoft, whitenStrength);

outDir = fullfile(scriptDir, 'output_beauty');
if ~exist(outDir, 'dir')
    mkdir(outDir);
end

imwrite(maskBinary, fullfile(outDir, '01_skin_mask_binary.png'));
imwrite(maskSoft, fullfile(outDir, '02_skin_mask_soft.png'));
imwrite(smoothResult, fullfile(outDir, '03_smooth_result.png'));
imwrite(finalResult, fullfile(outDir, '04_final_beauty.png'));
imwrite([I finalResult], fullfile(outDir, '05_compare_original_final.png'));

figure('Name', '人像美颜实验结果');
subplot(2,3,1); imshow(I); title('原图');
subplot(2,3,2); imshow(maskBinary); title('皮肤检测掩膜');
subplot(2,3,3); imshow(maskSoft, []); title('羽化后的掩膜');
subplot(2,3,4); imshow(smoothResult); title('磨皮结果');
subplot(2,3,5); imshow(finalResult); title('最终美颜结果');
subplot(2,3,6); imshow([I finalResult]); title('原图 / 最终结果');

disp(['处理完成，结果已保存到：' outDir]);


function [mask, maskSoft] = detectSkinYCbCr(I)
% 组合 YCbCr、RGB 和 HSV 条件检测皮肤。
% 不使用 imfill 填洞，避免眼睛、眉毛和嘴部被误当成皮肤。

ycbcr = rgb2ycbcr(I);
Y  = ycbcr(:,:,1);
Cb = ycbcr(:,:,2);
Cr = ycbcr(:,:,3);

R = I(:,:,1);
G = I(:,:,2);
B = I(:,:,3);
hsvImg = rgb2hsv(I);
S = hsvImg(:,:,2);

% YCbCr 给出主要肤色范围；RGB/HSV 条件排除白背景、头发和蓝眼睛。
ycbcrSkin = Cb >= 77/255 & Cb <= 127/255 & ...
            Cr >= 133/255 & Cr <= 178/255 & Y >= 35/255;
rgbSkin = R > 0.20 & G > 0.12 & B > 0.08 & ...
          R > G & R > B & (R - G) > 0.015;
hsvSkin = S >= 0.06 & S <= 0.78;

mask = ycbcrSkin & rgbSkin & hsvSkin;

% 只连接很小的断裂并去除噪点；保留五官形成的非皮肤孔洞。
mask = imclose(mask, makeDisk(3));
mask = imopen(mask, makeDisk(1));
mask = bwareaopen(mask, 80);

% 羽化边界，且让较暗、饱和度很高的五官区域获得更小权重。
maskSoft = imgaussfilt(double(mask), 4);
lightWeight = min(max((Y - 0.10) / 0.18, 0), 1);
satProtection = 1 - 0.70 * min(max((S - 0.48) / 0.30, 0), 1);
maskSoft = maskSoft .* lightWeight .* satProtection;
maskSoft = max(0, min(1, maskSoft));

end


function result = smoothSkin(I, maskSoft, strength)

bilateralResult = zeros(size(I));
if exist('imbilatfilt', 'file') == 2
    for c = 1:3
        bilateralResult(:,:,c) = imbilatfilt( ...
            I(:,:,c), 0.03 + 0.04 * strength, 8 + 8 * strength);
    end
else
    for c = 1:3
        bilateralResult(:,:,c) = imgaussfilt(I(:,:,c), 2.0);
    end
end

gaussianResult = zeros(size(I));
for c = 1:3
    gaussianResult(:,:,c) = imgaussfilt(I(:,:,c), 1.5 + 2.0 * strength);
end

smoothBase = 0.75 * bilateralResult + 0.25 * gaussianResult;
alpha = repmat(maskSoft * strength, [1 1 3]);
result = I .* (1 - alpha) + smoothBase .* alpha;
result = max(0, min(1, result));

end


function result = whitenSkinHSV(I, maskSoft, strength)

hsvImg = rgb2hsv(I);
H = hsvImg(:,:,1);
S = hsvImg(:,:,2);
V = hsvImg(:,:,3);

V2 = V .* (1 + 0.25 * strength) + 0.03 * strength;
S2 = S .* (1 - 0.18 * strength);
V2 = max(0, min(1, V2));
S2 = max(0, min(1, S2));

whiteImg = hsv2rgb(cat(3, H, S2, V2));
alpha = repmat(maskSoft, [1 1 3]);
result = I .* (1 - alpha) + whiteImg .* alpha;
result = max(0, min(1, result));

end


function se = makeDisk(r)

try
    se = strel('disk', r);
catch
    se = strel('disk', r, 0);
end

end
