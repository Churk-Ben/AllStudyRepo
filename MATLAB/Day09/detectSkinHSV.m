function mask = detectSkinHSV(I)
hsvImg = rgb2hsv(I);
H = hsvImg(:,:,1); S = hsvImg(:,:,2); V = hsvImg(:,:,3);
redHue = H <= 0.12 | H >= 0.96;
mask = redHue & S >= 0.15 & S <= 0.75 & V >= 0.25;
end
