clear; clc; close all;

img = im2double(imread('rice.png'));
lap4 = [0 1 0; 1 -4 1; 0 1 0];
lap8 = [1 1 1; 1 -8 1; 1 1 1];

L4 = imfilter(img, lap4, 'replicate');
L8 = imfilter(img, lap8, 'replicate');
sharp4 = img - L4;
sharp8 = img - L8;

figure;
subplot(2,2,1); imshow(img); title('原图');
subplot(2,2,2); imshow(L4, []); title('4邻域拉普拉斯');
subplot(2,2,3); imshow(sharp4, []); title('4邻域锐化');
subplot(2,2,4); imshow(sharp8, []); title('8邻域锐化');