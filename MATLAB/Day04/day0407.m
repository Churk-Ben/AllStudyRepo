clear; clc; close all;

lena = im2double(rgb2gray(imread('lena.png')));

% 生成LoG核
sigma1 = 1; sz1 = 5;
sigma2 = 2; sz2 = 9;
log1 = fspecial('log', sz1, sigma1);
log2 = fspecial('log', sz2, sigma2);

% 显示核曲面
figure;
subplot(1,2,1); surf(log1); title('LoG核 σ=1, 尺寸5');
subplot(1,2,2); surf(log2); title('LoG核 σ=2, 尺寸9');

% 滤波结果
resp1 = imfilter(lena, log1, 'replicate');
resp2 = imfilter(lena, log2, 'replicate');

figure;
subplot(1,3,1); imshow(lena); title('原图Lena');
subplot(1,3,2); imshow(resp1, []); title('LoG响应 σ=1');
subplot(1,3,3); imshow(resp2, []); title('LoG响应 σ=2');