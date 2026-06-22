%% 引导滤波磨皮函数
function smoothed = guidedFilterSmoothing(img, maskSoft, strength)
    % 参数自适应
    r   = round(8 + 8 * strength);
    eps = (0.01 + 0.02 * (1 - strength))^2;
    
    % ========== 步骤1：标准引导滤波（提取低频层/基础层） ==========
    base = zeros(size(img));
    for c = 1:3
        I = img(:,:,c);
        p = img(:,:,c);
        
        mean_I  = imboxfilt(I, 2*r+1);
        mean_p  = imboxfilt(p, 2*r+1);
        mean_Ip = imboxfilt(I .* p, 2*r+1);
        mean_II = imboxfilt(I .* I, 2*r+1);
        
        var_I  = mean_II - mean_I.^2;
        cov_Ip = mean_Ip - mean_I .* mean_p;
        
        a = cov_Ip ./ (var_I + eps);
        b = mean_p - a .* mean_I;
        
        mean_a = imboxfilt(a, 2*r+1);
        mean_b = imboxfilt(b, 2*r+1);
        
        base(:,:,c) = mean_a .* I + mean_b;
    end
    
    % ========== 步骤2：高频层斑点抑制（核心改进） ==========
    highFreq = img - base;  % 高频层包含纹理、毛孔、孤立斑点
    
    for c = 1:3
        hf = highFreq(:,:,c);
        
        % 3x3 中值滤波：专门抑制脉冲状孤立斑点，保留边缘纹理
        hf_median = medfilt2(hf, [3 3]);
        
        % 根据磨皮强度混合：strength越大，斑点抑制越强
        highFreq(:,:,c) = (1 - strength * 0.8) * hf + strength * 0.8 * hf_median;
    end
    
    % 重建
    smoothed = base + highFreq;
    smoothed = max(0, min(1, smoothed));
    
    % 根据磨皮强度保留部分原图细节（避免塑料感）
    detail = img - smoothed;
    smoothed = smoothed + (1 - strength) * detail;
    smoothed = max(0, min(1, smoothed));
end