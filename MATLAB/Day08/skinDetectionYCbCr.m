%% 肤色检测函数（YCbCr色彩空间+椭圆模型）
function [skinMask, skinProb, maskSoft] = skinDetectionYCbCr(img)
    % 转换到各色彩空间
    ycbcr = rgb2ycbcr(img);
    Y  = ycbcr(:,:,1);
    Cb = ycbcr(:,:,2);
    Cr = ycbcr(:,:,3);
    
    R = img(:,:,1);
    G = img(:,:,2);
    B = img(:,:,3);
    
    hsvImg = rgb2hsv(img);
    S = hsvImg(:,:,2);
    
    % 1. YCbCr 给出主要肤色范围
    ycbcrSkin = Cb >= 77/255 & Cb <= 127/255 & ...
                Cr >= 133/255 & Cr <= 178/255 & Y >= 35/255;
    
    % 2. RGB 条件排除白背景、头发和蓝眼睛
    rgbSkin = R > 0.20 & G > 0.12 & B > 0.08 & ...
              R > G & R > B & (R - G) > 0.015;
    
    % 3. HSV 条件排除高饱和度非皮肤区域（保护嘴唇、眼影）
    hsvSkin = S >= 0.06 & S <= 0.78;
    
    % 联合检测（取交集，显著减少误检）
    skinMask = ycbcrSkin & rgbSkin & hsvSkin;
    
    % 形态学处理：只连接很小的断裂并去除噪点；
    % 保留五官形成的非皮肤孔洞（不使用imfill）
    skinMask = imclose(skinMask, makeDisk(3));
    skinMask = imopen(skinMask, makeDisk(1));
    skinMask = bwareaopen(skinMask, 80);
    
    % 保留原有椭圆模型概率（供后续分析或自适应使用）
    Cb_scaled = Cb * 255;
    Cr_scaled = Cr * 255;
    Y_scaled  = Y  * 255;
    cx = 109.38; cy = 152.02;
    a = 25.39; b = 14.03; theta = 2.53;
    a_adj = a * (1 + 0.1 * (Y_scaled > 230));
    b_adj = b * (1 + 0.1 * (Y_scaled > 230));
    cos_t = cos(theta); sin_t = sin(theta);
    term1 = ((cos_t .* (Cb_scaled - cx) + sin_t .* (Cr_scaled - cy)) ./ a_adj).^2;
    term2 = ((-sin_t .* (Cb_scaled - cx) + cos_t .* (Cr_scaled - cy)) ./ b_adj).^2;
    ellipseValue = term1 + term2;
    skinProb = exp(-ellipseValue / 2);
    
    % 生成自适应软蒙版（关键改进，替代原有的简单processSkinMask）
    maskSoft = imgaussfilt(double(skinMask), 4);
    
    % 亮度权重：较暗区域（眉毛、眼睛、鼻孔阴影）获得更小权重
    lightWeight = min(max((Y - 0.10) / 0.18, 0), 1);
    
    % 饱和度保护：高饱和度区域（嘴唇、眼影）获得更小权重
    satProtection = 1 - 0.70 * min(max((S - 0.48) / 0.30, 0), 1);
    
    % 综合：基础羽化 × 亮度权重 × 饱和度保护
    maskSoft = maskSoft .* lightWeight .* satProtection;
    maskSoft = max(0, min(1, maskSoft));
end