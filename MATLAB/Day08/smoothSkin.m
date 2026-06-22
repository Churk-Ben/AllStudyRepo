function result = smoothSkin(I, maskSoft, strength)
%% smoothSkin  磨皮（双边滤波 + 频率分离去斑点 + 高斯柔化）
%   输入 : I        - 原图 (double [0,1])
%          maskSoft - 软掩膜
%          strength - 磨皮强度 (0~1)
%   输出 : result   - 磨皮后图像
%
%   流程：1) 双边滤波提取低频层；2) 高频层做中值滤波去孤立斑点；
%         3) 重建后与轻度高斯模糊按 0.75:0.25 混合；4) 按 maskSoft 融合。

    % ---------- 步骤1：双边滤波（保边低频层） ----------
    bilateralResult = zeros(size(I));
    if exist('imbilatfilt', 'file') == 2
        for c = 1:3
            bilateralResult(:,:,c) = imbilatfilt( ...
                I(:,:,c), ...
                0.03 + 0.04 * strength, ...
                8 + 8 * strength);
        end
    else
        % 降级方案：若 MATLAB 版本无 imbilatfilt，用高斯近似
        for c = 1:3
            bilateralResult(:,:,c) = imgaussfilt(I(:,:,c), 2.0);
        end
    end

    % ---------- 步骤2：频率分离 —— 高频层斑点抑制 ----------
    highFreq = I - bilateralResult;   % 高频层含纹理、毛孔、孤立斑点

    for c = 1:3
        hf = highFreq(:,:,c);

        % 3x3 中值滤波专门抑制脉冲状孤立斑点，保留边缘纹理
        hf_denoised = medfilt2(hf, [3 3]);

        % 按强度混合：strength 越大，斑点抑制越激进
        blend = strength * 0.7;
        highFreq(:,:,c) = (1 - blend) * hf + blend * hf_denoised;
    end

    % 重建去斑后的双边结果
    bilateralDenoised = bilateralResult + highFreq;
    bilateralDenoised = max(0, min(1, bilateralDenoised));

    % ---------- 步骤3：轻度高斯柔化（提供基础平滑） ----------
    gaussianResult = zeros(size(I));
    for c = 1:3
        gaussianResult(:,:,c) = imgaussfilt(I(:,:,c), 1.5 + 2.0 * strength);
    end

    % ---------- 步骤4：混合 ----------
    smoothBase = 0.75 * bilateralDenoised + 0.25 * gaussianResult;

    % ---------- 步骤5：按软掩膜与原图融合 ----------
    alpha = repmat(maskSoft * strength, [1 1 3]);
    result = I .* (1 - alpha) + smoothBase .* alpha;
    result = max(0, min(1, result));
end