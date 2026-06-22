function result = whitenSkinHSV(I, maskSoft, strength)
%% whitenSkinHSV  HSV 空间皮肤美白
%   输入 : I        - 输入图像 (double [0,1])
%          maskSoft - 软掩膜
%          strength - 美白强度 (0~1)
%   输出 : result   - 美白后图像
%
%   策略：提升 V（亮度）并轻微降低 S（饱和度），仅在 maskSoft 区域生效。

    hsvImg = rgb2hsv(I);
    H = hsvImg(:,:,1);
    S = hsvImg(:,:,2);
    V = hsvImg(:,:,3);

    % 亮度提升
    V2 = V .* (1 + 0.25 * strength) + 0.03 * strength;
    % 饱和度轻微降低，减少暗黄感
    S2 = S .* (1 - 0.18 * strength);

    % 截断到合法范围
    V2 = max(0, min(1, V2));
    S2 = max(0, min(1, S2));

    whiteImg = hsv2rgb(cat(3, H, S2, V2));

    % 按软掩膜融合
    alpha = repmat(maskSoft, [1 1 3]);
    result = I .* (1 - alpha) + whiteImg .* alpha;
    result = max(0, min(1, result));
end