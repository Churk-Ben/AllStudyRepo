function [result, supported] = bilateralSmoothSkin(I, maskSoft, strength)
supported = exist('imbilatfilt', 'file') == 2;
if ~supported
    result = gaussianSmoothSkin(I, maskSoft, strength);
    return;
end

filtered = zeros(size(I));
degree = 0.025 + 0.045*strength;
spatialSigma = 5 + 8*strength;
for c = 1:3
    filtered(:,:,c) = imbilatfilt(I(:,:,c), degree, spatialSigma);
end
result = blendByMask(I, filtered, maskSoft, strength);
end
