function result = smoothSkin_2(img, skinMask)
% SMOOTHSKIN_2  基于高斯模糊 + 细节提取的表面模糊磨皮
%   先大半径模糊, 再从中提取细节层, 削弱细节后重建,
%   达到类似"表面模糊"的去瑕疵效果.
%
%   result = smoothSkin_2(img, skinMask)
%
%   输入:
%       img      - HxWx3 double 原图 [0,1]
%       skinMask - HxW double 皮肤软掩膜 [0,1]
%   输出:
%       result   - HxWx3 double 磨皮后图像 [0,1]

    blurSigma = 3;
    blurred = imgaussfilt(img, blurSigma);   % 大幅模糊 → 低频层

    detail = img - blurred;                   % 高频细节
    detailStrength = 0.55;                    % 细节保留系数 (越小越光滑)
    smoothed = blurred + detail * detailStrength;

    % 仅皮肤区域混合
    result = img .* (1 - skinMask) + smoothed .* skinMask;

    fprintf('[smoothSkin_2] Surface-blur smoothing done (sigma=%.0f, detail=%.2f).\n', ...
            blurSigma, detailStrength);
end
