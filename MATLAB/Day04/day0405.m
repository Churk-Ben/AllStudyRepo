clear; clc; close all;

img = im2double(imread('rice.png'));

% 计算Sobel梯度
sobel_x = [-1 -2 -1; 0 0 0; 1 2 1];
sobel_y = [-1 0 1; -2 0 2; -1 0 1];
Gx = imfilter(img, sobel_x, 'replicate');
Gy = imfilter(img, sobel_y, 'replicate');
G = hypot(Gx, Gy);

% 五种锐化结果
T1 = 0.05; T2 = 0.08; T3 = 0.1; T4 = 0.12;
sharp1 = img + (G > T1) .* G;
sharp2 = img + 0.8 * G;
sharp3 = img + G .* (G > T2);
sharp4 = img + (G > T3) * 0.5;
sharp5 = img + G .* (G < T4);

figure;
subplot(2,3,1); imshow(img); title('原图');
subplot(2,3,2); imshow(sharp1, []); title('锐化方式1');
subplot(2,3,3); imshow(sharp2, []); title('锐化方式2');
subplot(2,3,4); imshow(sharp3, []); title('锐化方式3');
subplot(2,3,5); imshow(sharp4, []); title('锐化方式4');
subplot(2,3,6); imshow(sharp5, []); title('锐化方式5');