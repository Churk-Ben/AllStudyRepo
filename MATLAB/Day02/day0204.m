%% 直方图规定化（匹配）
img = imread("pout.tif");
target = imread("Fig0809(a).tif");

hgram_target = imhist(target);
matched = histeq(img, hgram_target);

subplot(2,3,1);
imshow(img);

subplot(2,3,2);
imhist(img)

subplot(2,3,4);
imshow(matched)

subplot(2,3,5);
imhist(matched)

subplot(2,3,[3,6])
imhist(target)