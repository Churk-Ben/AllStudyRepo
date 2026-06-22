function result = enhanceLip_1(img, lipMask)
% ENHANCELIP_1  唇部颜色增强
%   在 HSV 空间中对唇部区域提升饱和度,
%   并微调色调偏向红色, 让嘴唇更红润.
%
%   result = enhanceLip_1(img, lipMask)
%
%   输入:
%       img     - HxWx3 double 图像 [0,1]
%       lipMask - HxW double 唇部软掩膜 [0,1]
%   输出:
%       result  - HxWx3 double 唇色增强后图像 [0,1]

    hsv = rgb2hsv(img);
    H = hsv(:,:,1);
    S = hsv(:,:,2);
    V = hsv(:,:,3);

    % 色调向红色偏移: H 越接近 0 (红) 越保留, 否则略微拉向 0
    H_adj = H;
    redShift = 0.15;
    lipActive = lipMask > 0.2;
    % 将非红唇区域色调向 0 (红色) 收缩
    H_adj(lipActive) = H_adj(lipActive) * (1 - redShift);

    % 提升饱和度
    satBoost = 0.45;
    S_adj = min(S .* (1 + satBoost * lipMask), 1);

    hsvAdj = cat(3, H_adj, S_adj, V);
    enhanced = hsv2rgb(hsvAdj);

    result = img .* (1 - lipMask) + enhanced .* lipMask;

    fprintf('[enhanceLip_1] Lip color enhanced.\n');
end
