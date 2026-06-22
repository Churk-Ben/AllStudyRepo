function result = applyBlush_1(img, cheekMask)
% APPLYBLUSH_1  面颊腮红绘制
%   在面颊区域叠加粉色调, 按掩膜强度控制透明度,
%   产生自然的腮红效果.
%
%   result = applyBlush_1(img, cheekMask)
%
%   输入:
%       img       - HxWx3 double 图像 [0,1]
%       cheekMask - HxW double 面颊软掩膜 [0,1]
%   输出:
%       result    - HxWx3 double 腮红后图像 [0,1]

    % 腮红颜色 (粉色调)
    blushColor = [1.0, 0.45, 0.55];

    % 按掩膜强度计算透明度
    alpha = cheekMask * 0.38;          % 最大不透明度 38%
    alpha = min(alpha, 1);

    % 叠色: result = img * (1-alpha) + blush * alpha
    result = img;
    for c = 1:3
        result(:,:,c) = result(:,:,c) .* (1 - alpha) + blushColor(c) * alpha;
    end

    fprintf('[applyBlush_1] Blush applied.\n');
end
