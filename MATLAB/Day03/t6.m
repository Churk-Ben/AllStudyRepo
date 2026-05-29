I = im2double(imread("Fig0512(b)(ckt-uniform-plus-saltpepr-prob-pt1).tif"));

window_size = 3;
Q = 1;

I_arith = imfilter(I, ones(window_size)/window_size^2, 'replicate');
I_geo = exp(imfilter(log(I + 1e-6), ones(window_size)/window_size^2, 'replicate'));
I_harm = 1 ./ imfilter(1./(I + 1e-6), ones(window_size)/window_size^2, 'replicate');
I_contra = imfilter(I.^(Q+1), ones(window_size), 'replicate') ./ ...
           (imfilter(I.^Q, ones(window_size), 'replicate') + 1e-6);

figure('Name','四种均值滤波对比');
subplot(2,3,1); imshow(I); title('原图');
subplot(2,3,2); imshow(I_arith); title('算术均值滤波');
subplot(2,3,3); imshow(I_geo); title('几何均值滤波');
subplot(2,3,4); imshow(I_harm); title('谐波均值滤波');
subplot(2,3,5); imshow(I_contra); title(['逆谐波均值滤波 (Q=', num2str(Q), ')']);
