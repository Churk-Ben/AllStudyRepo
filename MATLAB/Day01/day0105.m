img = imread("pout.tif");
[h , w] = size(img);

min_p = min(img(:));
max_p = max(img(:));

k = 255 / (max_p - min_p);

img_p = img;
img_p(:) = k * (img(:) - min_p);

subplot(121); imshow(img);
subplot(122); imshow(img_p);