function [mask, maskSoft] = processSkinMask(mask, I)
mask = logical(mask);
mask = imopen(mask, makeDisk(1));
mask = imclose(mask, makeDisk(3));

% 只填充小孔，避免眼睛和嘴部被掩膜覆盖。
holes = imfill(mask, 'holes') & ~mask;
smallHoles = holes & ~bwareaopen(holes, 350);
mask = mask | smallHoles;
mask = bwareaopen(mask, 80);

maskSoft = imgaussfilt(double(mask), 4);
ycbcr = rgb2ycbcr(I);
Y = ycbcr(:,:,1);
hsvImg = rgb2hsv(I);
S = hsvImg(:,:,2);
lightWeight = min(max((Y-0.10)/0.18, 0), 1);
satProtection = 1 - 0.70*min(max((S-0.48)/0.30, 0), 1);
maskSoft = maskSoft .* lightWeight .* satProtection;
maskSoft = max(0, min(1, maskSoft));
end
