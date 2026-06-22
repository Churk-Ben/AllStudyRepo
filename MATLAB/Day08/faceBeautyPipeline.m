%% ============================================================
% 人像美颜算法完整MATLAB实现
% 功能：皮肤检测 + 引导滤波磨皮 + Gamma校正美白
% 作者：课程设计2
% ============================================================

%% 主函数：完整美颜流程
function result = faceBeautyPipeline(image, smoothStrength, whitenStrength)
    if nargin < 2
        smoothStrength = 0.7;
    end
    if nargin < 3
        whitenStrength = 0.4;
    end
    
    if isa(image, 'uint8')
        img = im2double(image);
    else
        img = image;
    end
    
    % 步骤1：皮肤区域检测（增强版多色彩空间联合检测）
    [skinMask, skinProb, maskSoft] = skinDetectionYCbCr(img);
    
    % 步骤2：引导滤波磨皮（含频率分离去斑点）
    smoothed = guidedFilterSmoothing(img, maskSoft, smoothStrength);
    
    % 步骤3：自适应Gamma美白
    whitened = adaptiveWhitening(img, maskSoft, whitenStrength);
    
    % 步骤4：融合（先磨皮，再美白，maskSoft控制空间过渡）
    beautyBlend = maskSoft .* smoothed + (1 - maskSoft) .* img;
    result      = maskSoft .* whitened + (1 - maskSoft) .* beautyBlend;
    result = max(0, min(1, result));
end