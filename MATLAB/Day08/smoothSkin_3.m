function result = smoothSkin_3(img, skinMask)
% SMOOTHSKIN_3  基于双边滤波的保边磨皮
%   使用 imbilatfilt 逐通道双边滤波, 保留边缘同时平滑皮肤纹理.
%   若不支持 imbilatfilt (旧版 MATLAB), 降级为引导滤波.
%
%   result = smoothSkin_3(img, skinMask)
%
%   输入:
%       img      - HxWx3 double 原图 [0,1]
%       skinMask - HxW double 皮肤软掩膜 [0,1]
%   输出:
%       result   - HxWx3 double 磨皮后图像 [0,1]

    if exist('imbilatfilt', 'file') == 2
        filtered = zeros(size(img));
        % 双边滤波参数: degree 控制强度, spatialSigma 控制空间范围
        degree       = 0.04;
        spatialSigma = 9;
        for c = 1:3
            filtered(:,:,c) = imbilatfilt(img(:,:,c), degree, spatialSigma);
        end
        fprintf('[smoothSkin_3] Bilateral filter smoothing done.\n');
    else
        % 降级: 引导滤波
        warning('imbilatfilt not available, falling back to guided filter.');
        if exist('imguidedfilter', 'file') == 2
            filtered = imguidedfilter(img, ...
                'NeighborhoodSize', [5 5], ...
                'DegreeOfSmoothing', 0.5);
        else
            filtered = imgaussfilt(img, 3);
        end
        fprintf('[smoothSkin_3] Fallback smoothing done.\n');
    end

    % 仅皮肤区域混合
    result = img .* (1 - skinMask) + filtered .* skinMask;

end
