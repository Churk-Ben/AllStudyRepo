function result = whitenSkin_2(img, skinMask)
% WHITENSKIN_2  基于 Gamma 曲线 + 降饱和的美白
%   对图像整体施加 Gamma < 1 的曲线提亮中间调,
%   并适度降低皮肤饱和度, 获得"通透白"效果.
%
%   result = whitenSkin_2(img, skinMask)
%
%   输入:
%       img      - HxWx3 double 原图 [0,1]
%       skinMask - HxW double 皮肤软掩膜 [0,1]
%   输出:
%       result   - HxWx3 double 美白后图像 [0,1]

    gamma = 0.82;   % <1 提亮中间调
    whitened = img .^ gamma;

    % 适度降低饱和度
    hsv = rgb2hsv(whitened);
    hsv(:,:,2) = hsv(:,:,2) * 0.82;
    whitened = hsv2rgb(hsv);

    % 仅皮肤区域混合
    result = img .* (1 - skinMask) + whitened .* skinMask;

    fprintf('[whitenSkin_2] Gamma-curve whitening done (gamma=%.2f).\n', gamma);
end
