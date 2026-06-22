function skinMask = detectSkin_2(img)
% DETECTSKIN_2  YCbCr 色彩空间皮肤软掩膜 (借鉴 Day09 流程)
%   1. Y/Cb/Cr 阈值 → 二值掩膜
%   2. 形态学开闭 + 孔洞填充 + 小面积去除
%   3. Y 亮度加权 + S 饱和度保护 → 高斯羽化软掩膜
%
%   skinMask = detectSkin_2(img)
%
%   输入:
%       img      - HxWx3 double 图像 [0,1]
%   输出:
%       skinMask - HxW double 软掩膜 [0,1]

    ycbcr = rgb2ycbcr(img);
    Y  = ycbcr(:,:,1);
    Cb = ycbcr(:,:,2);
    Cr = ycbcr(:,:,3);

    % ---- Step 1: 二值掩膜 (Day09 YCbCr 阈值) ----
    skinCb = (Cb >= 77/255)  & (Cb <= 127/255);
    skinCr = (Cr >= 133/255) & (Cr <= 173/255);
    skinY  = (Y  >  40/255)  & (Y  <  245/255);
    maskBin = skinCb & skinCr & skinY;

    % ---- Step 2: 形态学处理 ----
    maskBin = imopen(maskBin,  strel('disk', 1));
    maskBin = imclose(maskBin, strel('disk', 3));

    holes      = imfill(maskBin, 'holes') & ~maskBin;
    smallHoles = holes & ~bwareaopen(holes, 350);
    maskBin    = maskBin | smallHoles;

    maskBin = bwareaopen(maskBin, 80);

    % ---- Step 3: 亮度/饱和度加权 → 软掩膜 ----
    skinMask = imgaussfilt(double(maskBin), 4);

    lightWeight = min(max((Y - 0.10) / 0.18, 0), 1);

    hsvImg = rgb2hsv(img);
    S = hsvImg(:,:,2);
    satProtection = 1 - 0.70 * min(max((S - 0.48) / 0.30, 0), 1);

    skinMask = skinMask .* lightWeight .* satProtection;
    skinMask = max(0, min(1, skinMask));

    fprintf('[detectSkin_2] YCbCr soft skin mask generated.\n');
end
