function result = medianSmoothSkin(I, maskSoft, strength)
filtered = zeros(size(I));
kernelSize = 3 + 2*(strength > 0.55);
for c = 1:3
    filtered(:,:,c) = medfilt2(I(:,:,c), ...
        [kernelSize kernelSize], 'symmetric');
end
result = blendByMask(I, filtered, maskSoft, strength);
end
