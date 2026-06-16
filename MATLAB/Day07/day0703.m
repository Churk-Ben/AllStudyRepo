img = im2double(imread('Fig1046(a)(septagon_noisy_shaded).tif'));

% 预处理：中值滤波去噪 + 自适应直方图均衡化
img_med = medfilt2(img, [3 3]);
img_eq  = adapthisteq(img_med);

% 全局阈值二值化
T = graythresh(img_eq);
bw = imbinarize(img_eq, T);

% 形态学后处理
bw = imopen(bw,  strel('disk', 2));
bw = imclose(bw, strel('disk', 2));

figure;
subplot(1,3,1); imshow(img,[]);     title('原图');
subplot(1,3,2); imshow(img_eq,[]);  title('增强图像');
subplot(1,3,3); imshow(bw,[]);      title('分割结果');