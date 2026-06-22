function [result, supported] = guidedSmoothSkin(I, maskSoft, strength)
supported = exist('imguidedfilter', 'file') == 2;
if ~supported
    result = gaussianSmoothSkin(I, maskSoft, strength);
    return;
end

filtered = zeros(size(I));
windowSize = 5 + 2*round(3*strength);
if mod(windowSize, 2) == 0
    windowSize = windowSize + 1;
end
for c = 1:3
    filtered(:,:,c) = imguidedfilter(I(:,:,c), ...
        'NeighborhoodSize', [windowSize windowSize], ...
        'DegreeOfSmoothing', 0.0005 + 0.003*strength);
end
result = blendByMask(I, filtered, maskSoft, strength);
end
