function mask = detectSkinYCbCr(I)
ycbcr = rgb2ycbcr(I);
Y = ycbcr(:,:,1); Cb = ycbcr(:,:,2); Cr = ycbcr(:,:,3);
mask = Cb >= 77/255 & Cb <= 127/255 & ...
       Cr >= 133/255 & Cr <= 173/255 & ...
       Y > 40/255 & Y < 245/255;
end
