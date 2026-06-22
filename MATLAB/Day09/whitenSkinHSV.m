function result = whitenSkinHSV(I, maskSoft, strength)
hsvImg = rgb2hsv(I);
H = hsvImg(:,:,1); S = hsvImg(:,:,2); V = hsvImg(:,:,3);
S2 = max(0, min(1, S.*(1-0.18*strength)));
V2 = max(0, min(1, V.*(1+0.25*strength)+0.03*strength));
whiteImg = hsv2rgb(cat(3, H, S2, V2));
result = blendByMask(I, whiteImg, maskSoft, 1.0);
end
