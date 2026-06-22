function skinMask = detectSkin_1(img)
% DETECTSKIN_1  HSV 色彩空间皮肤软掩膜 (借鉴 Day09 流程)
%   1. H/S/V 阈值 → 二值掩膜
%   2. 形态学开闭 + 孔洞填充 + 小面积去除
%   3. Y 亮度加权 + S 饱和度保护 → 高斯羽化软掩膜
%
%   skinMask = detectSkin_1(img)
%
%   输入:
%       img      - HxWx3 double 图像 [0,1]
%   输出:
%       skinMask - HxW double 软掩膜 [0,1]

    hsvImg = rgb2hsv(img);
    H = hsvImg(:,:,1);
    S = hsvImg(:,:,2);
    V = hsvImg(:,:,3);

    % ---- Step 1: 二值掩膜 (Day09 HSV 阈值) ----
    redHue    = (H <= 0.12) | (H >= 0.96);
    skinSat   = (S >= 0.15) & (S <= 0.75);
    skinVal   = (V >= 0.25);
    maskBin   = redHue & skinSat & skinVal;

    % ---- Step 2: 形态学处理 ----
    maskBin = imopen(maskBin,  strel('disk', 1));
    maskBin = imclose(maskBin, strel('disk', 3));

    % 填充小孔, 避免把眼睛/嘴巴填进来
    holes      = imfill(maskBin, 'holes') & ~maskBin;
    smallHoles = holes & ~bwareaopen(holes, 350);
    maskBin    = maskBin | smallHoles;

    % 去除小面积噪点
    maskBin = bwareaopen(maskBin, 80);

    % ---- Step 3: 亮度/饱和度加权 → 软掩膜 ----
    skinMask = imgaussfilt(double(maskBin), 4);

    % Y 亮度加权: 过暗区域降权, 避免头发/阴影误判
    ycbcr   = rgb2ycbcr(img);
    Y       = ycbcr(:,:,1);
    lightWeight = min(max((Y - 0.10) / 0.18, 0), 1);

    % S 饱和度保护: 过高饱和度区域降权 (不自然肤色)
    satProtection = 1 - 0.70 * min(max((S - 0.48) / 0.30, 0), 1);

    skinMask = skinMask .* lightWeight .* satProtection;
    skinMask = max(0, min(1, skinMask));

    fprintf('[detectSkin_1] HSV soft skin mask generated.\n');
end
