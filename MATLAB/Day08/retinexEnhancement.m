%% 多尺度Retinex美白增强函数
function enhanced = retinexEnhancement(img, strength)
    logImg = log1p(img);
    sigma1 = 15; sigma2 = 80; sigma3 = 250;
    
    blur1 = imgaussfilt(img, sigma1);
    blur2 = imgaussfilt(img, sigma2);
    blur3 = imgaussfilt(img, sigma3);
    
    logBlur1 = log1p(blur1);
    logBlur2 = log1p(blur2);
    logBlur3 = log1p(blur3);
    
    w1 = 1/3; w2 = 1/3; w3 = 1/3;
    logR = w1 * (logImg - logBlur1) + ...
           w2 * (logImg - logBlur2) + ...
           w3 * (logImg - logBlur3);
    
    R = expm1(logR);
    R = mat2gray(R);
    enhanced = (1 - strength) * img + strength * R;
end