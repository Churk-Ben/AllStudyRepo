clear; clc; close all;

img = im2double(imread("Fig0512(b)(ckt-uniform-plus-saltpepr-prob-pt1).tif"));
win = 3;
d = win^2;
alpha = 0.1;
trim = round(d * alpha);

% 算术均值
h = ones(win)/d;
arith = imfilter(img, h, 'replicate');

% 几何均值
geo = exp(imfilter(log(img + eps), h, 'replicate'));

% 中值滤波
med = medfilt2(img, [win win]);

% Alpha修剪均值
pad = floor(win/2);
img_pad = padarray(img, [pad pad], 'replicate');
alpha_mean = zeros(size(img));
for i = 1:size(img,1)
    for j = 1:size(img,2)
        block = img_pad(i:i+win-1, j:j+win-1);
        vec = sort(block(:));
        alpha_mean(i,j) = mean(vec(trim+1:end-trim));
    end
end

figure;
subplot(2,3,1); imshow(img); title('原图');
subplot(2,3,2); imshow(arith); title('算术均值');
subplot(2,3,3); imshow(geo); title('几何均值');
subplot(2,3,4); imshow(med); title('中值滤波');
subplot(2,3,5); imshow(alpha_mean); title('α修正均值');