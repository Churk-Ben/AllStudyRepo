function [result, lipMaskSoft] = enhanceLipColor(I)
[height, width, ~] = size(I);
hsvImg = rgb2hsv(I);
H = hsvImg(:,:,1); S = hsvImg(:,:,2); V = hsvImg(:,:,3);
R = I(:,:,1); G = I(:,:,2); B = I(:,:,3);

% 用嘴部中心附近的椭圆限制候选区域，排除鼻尖和人中阴影。
[xGrid, yGrid] = meshgrid(1:width, 1:height);
centerX = 0.52*width;
centerY = 0.545*height;
radiusX = 0.19*width;
radiusY = 0.050*height;
roi = ((xGrid-centerX)/radiusX).^2 + ...
      ((yGrid-centerY)/radiusY).^2 <= 1;

redHue = H <= 0.08 | H >= 0.94;
redness = R - 0.5*(G+B);
lipMask = roi & redHue & S >= 0.30 & V >= 0.18 & ...
          redness >= 0.25 & R > 1.15*G & R > 1.12*B;
lipMask = imopen(lipMask, makeDisk(1));
lipMask = imclose(lipMask, makeDisk(2));
lipMask = bwareaopen(lipMask, 15);
if any(lipMask(:))
    lipMask = bwareafilt(lipMask, 1);
end
lipMaskSoft = imgaussfilt(double(lipMask), 2.0);
lipMaskSoft = max(0, min(1, lipMaskSoft));

H2 = H;
lowRed = H <= 0.12;
H2(lowRed) = 0.65*H(lowRed);
highRed = H >= 0.92;
H2(highRed) = 1 - 0.65*(1-H(highRed));
S2 = min(1, S*1.30);
V2 = min(1, V*1.03);
colored = hsv2rgb(cat(3, H2, S2, V2));
result = blendByMask(I, colored, lipMaskSoft, 0.75);
end
