function mask = detectSkinRGB(I)
R = I(:,:,1); G = I(:,:,2); B = I(:,:,3);
channelMax = max(I, [], 3);
channelMin = min(I, [], 3);
mask = R > 95/255 & G > 40/255 & B > 20/255 & ...
       R > G & R > B & abs(R-G) > 15/255 & ...
       channelMax-channelMin > 15/255;
end
