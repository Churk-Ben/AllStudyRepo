function result = whitenSkin_1(img, skinMask)
% WHITENSKIN_1  HSV 空间亮度/饱和度调整美白
%   在 HSV 空间中对皮肤区域提升明度 V、降低饱和度 S,
%   模拟常见的"提亮去黄"美白效果.
%
%   result = whitenSkin_1(img, skinMask)
%
%   输入:
%       img      - HxWx3 double 原图 [0,1]
%       skinMask - HxW double 皮肤软掩膜 [0,1]
%   输出:
%       result   - HxWx3 double 美白后图像 [0,1]

    hsv = rgb2hsv(img);
    H = hsv(:,:,1);
    S = hsv(:,:,2);
    V = hsv(:,:,3);

    % 提亮明度, 降低饱和度 (值域限制在 [0,1])
    brightFactor = 0.18;
    satReduce    = 0.25;

    V_adj = min(V .* (1 + brightFactor * skinMask), 1);
    S_adj = max(S .* (1 - satReduce    * skinMask), 0);

    hsvAdj = cat(3, H, S_adj, V_adj);
    whitened = hsv2rgb(hsvAdj);

    % 仅皮肤区域混合
    result = img .* (1 - skinMask) + whitened .* skinMask;

    fprintf('[whitenSkin_1] HSV brightness/saturation whitening done.\n');
end
