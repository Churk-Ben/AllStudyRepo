%% 自适应美白函数（Gamma校正）
function whitened = adaptiveWhitening(img, maskSoft, strength)
    ycbcr = rgb2ycbcr(img);
    Y  = ycbcr(:,:,1);
    Cb = ycbcr(:,:,2);
    Cr = ycbcr(:,:,3);
    
    % Gamma校正：strength越大，gamma越小，提亮越多
    gamma = 1 - 0.4 * strength;  % 范围 0.6 ~ 1.0
    Y_whitened = Y .^ gamma;
    
    % 适度提升Cb（偏蓝）以中和黄色调
    Cb_adjusted = Cb - 0.02 * strength;
    % 适度降低Cr（偏红）使肤色更白皙
    Cr_adjusted = Cr - 0.02 * strength;
    
    ycbcr_whitened = cat(3, Y_whitened, Cb_adjusted, Cr_adjusted);
    whitened = ycbcr2rgb(ycbcr_whitened);
    whitened = max(0, min(1, whitened));
end
