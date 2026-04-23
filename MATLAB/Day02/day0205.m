img = imread("pout.tif");
out = adapthisteq(img);

subplot(2,2,1);
imshow(img);

subplot(2,2,2);
imhist(img)

subplot(2,2,3);
imshow(out)

subplot(2,2,4);
imhist(out)
