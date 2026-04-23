Eight = imread("eight.tif");
Rice = imread("rice.png");
Moon = imread("Fig0338(a)(blurry_moon).tif");

threshold = 128;
EightBin = Eight >= threshold;
RiceBin = Rice >= threshold;
MoonBin = Moon >= threshold;

subplot(3,3,1)
imshow(Eight)

subplot(3,3,2)
imhist(Eight)

subplot(3,3,3)
imshow(EightBin)

subplot(3,3,4)
imshow(Rice)

subplot(3,3,5)
imhist(Rice)

subplot(3,3,6)
imshow(RiceBin)

subplot(3,3,7)
imshow(Moon)

subplot(3,3,8)
imhist(Moon)

subplot(3,3,9)
imshow(MoonBin)