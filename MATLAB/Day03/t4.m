I = im2double(imread("Fig0507(b)(ckt-board-gauss-var-400).tif"));

window_size = 5;
I_arith = imfilter(I, ones(window_size)/window_size^2, 'replicate');
I_geo = exp(imfilter(log(I + 1e-6), ones(window_size)/window_size^2, 'replicate'));

figure('Name','算术均值 vs 几何均值滤波');
subplot(1,3,1); imshow(I); title('噪声原图');
subplot(1,3,2); imshow(I_arith); title('算术均值滤波');
subplot(1,3,3); imshow(I_geo); title('几何均值滤波');
