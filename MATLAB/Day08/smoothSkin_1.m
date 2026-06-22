function result = smoothSkin_1(img, skinMask)
% SMOOTHSKIN_1  基于引导滤波的保边磨皮
%   使用 imguidedfilter 对图像进行边缘保持平滑,
%   仅对皮肤区域生效, 非皮肤区域保留原图.
%
%   result = smoothSkin_1(img, skinMask)
%
%   输入:
%       img      - HxWx3 double 原图 [0,1]
%       skinMask - HxW double 皮肤软掩膜 [0,1]
%   输出:
%       result   - HxWx3 double 磨皮后图像 [0,1]

    if exist('imguidedfilter', 'file') == 2
        % 引导滤波: 保边平滑
        smoothed = imguidedfilter(img, ...
            'NeighborhoodSize', [5 5], ...
            'DegreeOfSmoothing', 0.5);
    else
        % 降级: 逐通道高斯模糊
        smoothed = zeros(size(img));
        for c = 1:3
            smoothed(:,:,c) = imgaussfilt(img(:,:,c), 2);
        end
    end

    % 仅在皮肤区域混合
    result = img .* (1 - skinMask) + smoothed .* skinMask;

    fprintf('[smoothSkin_1] Guided-filter smoothing done.\n');
end
