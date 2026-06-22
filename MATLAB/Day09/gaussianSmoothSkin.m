function result = gaussianSmoothSkin(I, maskSoft, strength)
filtered = zeros(size(I));
sigma = 1.2 + 2.3*strength;
for c = 1:3
    filtered(:,:,c) = imgaussfilt(I(:,:,c), sigma);
end
result = blendByMask(I, filtered, maskSoft, strength);
end
