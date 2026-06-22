function [smoothResult, finalResult] = runBeautyPipeline( ...
    I, maskSoft, smoothStrength, whitenStrength)
smoothResult = smoothSkin(I, maskSoft, smoothStrength);
finalResult = whitenSkinHSV(smoothResult, maskSoft, whitenStrength);
end
