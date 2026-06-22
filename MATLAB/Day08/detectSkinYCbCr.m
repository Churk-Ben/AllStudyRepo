function [mask, maskSoft] = detectSkinYCbCr(I)
%% detectSkinYCbCr  多色彩空间联合皮肤检测
%   输入 : I  - double 类型 RGB 图像，范围 [0,1]
%   输出 : mask     - 二值硬掩膜 (logical)
%          maskSoft - 羽化 + 自适应权重软掩膜 (double [0,1])
%
%   策略：YCbCr 划定主肤色范围；RGB 排除白背景/蓝眼睛；
%         HSV 排除高饱和非皮肤区域。不使用 imfill，保留五官孔洞。

    % ----- 色彩空间转换 -----
    ycbcr = rgb2ycbcr(I);
    Y  = ycbcr(:,:,1);
    Cb = ycbcr(:,:,2);
    Cr = ycbcr(:,:,3);

    R = I(:,:,1);
    G = I(:,:,2);
    B = I(:,:,3);

    hsvImg = rgb2hsv(I);
    S = hsvImg(:,:,2);

    % ----- 联合阈值检测 -----
    ycbcrSkin = Cb >= 77/255 & Cb <= 127/255 & ...
                Cr >= 133/255 & Cr <= 178/255 & ...
                Y  >= 35/255;

    rgbSkin = R > 0.20 & G > 0.12 & B > 0.08 & ...
              R > G & R > B & (R - G) > 0.015;

    hsvSkin = S >= 0.06 & S <= 0.78;

    mask = ycbcrSkin & rgbSkin & hsvSkin;

    % ----- 形态学后处理（去噪点，保留五官孔洞） -----
    mask = imclose(mask, makeDisk(3));
    mask = imopen(mask, makeDisk(1));
    mask = bwareaopen(mask, 80);

    % ----- 生成自适应软掩膜 -----
    maskSoft = imgaussfilt(double(mask), 4);

    % 亮度权重：压暗区域（眉毛、瞳孔、鼻孔）权重降低
    lightWeight = min(max((Y - 0.10) / 0.18, 0), 1);

    % 饱和度保护：高饱和区域（嘴唇、眼影）权重降低
    satProtection = 1 - 0.70 * min(max((S - 0.48) / 0.30, 0), 1);

    % 综合
    maskSoft = maskSoft .* lightWeight .* satProtection;
    maskSoft = max(0, min(1, maskSoft));
end