%% 双边滤波磨皮函数（备用方案）
function smoothed = bilateralFilterSmoothing(img, skinMask, strength)
    % 双边滤波参数
    d = 9;                    % 核直径
    sigmaColor = 0.1 + 0.1 * strength;  % 颜色空间sigma
    sigmaSpace = 10 + 5 * strength;     % 空间sigma
    
    % 对每个通道分别进行双边滤波
    smoothed = zeros(size(img));
    for c = 1:3
        smoothed(:,:,c) = imbilatfilt(img(:,:,c), sigmaColor, sigmaSpace, ...
            'NeighborhoodSize', d);
    end
end
