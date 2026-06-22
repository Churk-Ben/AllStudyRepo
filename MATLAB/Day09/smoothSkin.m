function result = smoothSkin(I, maskSoft, strength)
[bilateralResult, supported] = bilateralSmoothSkin(I, maskSoft, strength);
gaussianResult = gaussianSmoothSkin(I, maskSoft, strength);
if supported
    result = 0.80*bilateralResult + 0.20*gaussianResult;
else
    result = gaussianResult;
end
result = max(0, min(1, result));
end
