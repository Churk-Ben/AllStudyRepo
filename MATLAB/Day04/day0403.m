clear; clc; close all;

img = im2double(imread('rice.png'));

% 定义算子
roberts_x = [1 0; 0 -1];
roberts_y = [0 1; -1 0];
prewitt_x = [-1 -1 -1; 0 0 0; 1 1 1];
prewitt_y = [-1 0 1; -1 0 1; -1 0 1];
sobel_x = [-1 -2 -1; 0 0 0; 1 2 1];
sobel_y = [-1 0 1; -2 0 2; -1 0 1];

% 计算梯度幅值
grad_rob = hypot(imfilter(img, roberts_x, 'replicate'), ...
                 imfilter(img, roberts_y, 'replicate'));
grad_pre = hypot(imfilter(img, prewitt_x, 'replicate'), ...
                 imfilter(img, prewitt_y, 'replicate'));
grad_sob = hypot(imfilter(img, sobel_x, 'replicate'), ...
                 imfilter(img, sobel_y, 'replicate'));

figure;
subplot(2,2,1); imshow(img); title('原图');
subplot(2,2,2); imshow(grad_rob, []); title('Roberts');
subplot(2,2,3); imshow(grad_pre, []); title('Prewitt');
subplot(2,2,4); imshow(grad_sob, []); title('Sobel');