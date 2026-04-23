function Out = histeqSelf(In)
    [counts, ~] = imhist(In);
    cdf = cumsum(counts) / sum(counts);     % 归一化累积分布
    map = round(255 * cdf);                 % 映射表
    Out = intlut(In, uint8(map));           % 查表映射
end

Pout = imread("pout.tif");
PoutEq = histeqSelf(Pout);

subplot(2,2,1);
imshow(Pout);

subplot(2,2,2);
imhist(Pout)

subplot(2,2,3);
imshow(PoutEq)

subplot(2,2,4);
imhist(PoutEq)