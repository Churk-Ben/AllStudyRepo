%% 唇色增强（扩展功能）
function result = lipEnhancement(img, lipMask, hueShift, satBoost)
    if nargin < 4
        satBoost = 1.3;
    end
    if nargin < 3
        hueShift = 0.05;
    end
    
    hsv = rgb2hsv(img);
    H = hsv(:,:,1);
    S = hsv(:,:,2);
    V = hsv(:,:,3);
    
    lipMaskSmooth = imgaussfilt(lipMask, 3);
    H = mod(H + hueShift * lipMaskSmooth, 1);
    S = S .* (1 + (satBoost - 1) * lipMaskSmooth);
    S = min(S, 1);
    
    hsv_enhanced = cat(3, H, S, V);
    result = hsv2rgb(hsv_enhanced);
end