img = im2double(imread('Fig0525(b)(aerial_view_turb_c_0pt0025).tif'));
[M,N] = size(img);
[U,V] = meshgrid(-N/2:N/2-1, -M/2:M/2-1);
F_shift = fftshift(fft2(img));

% 退化函数（已知湍流强度 k=0.0025）
k = 0.0025;
H = exp(-k * (U.^2 + V.^2).^(5/6));

% 逆滤波（加阈值抑制噪声放大）
thresh = 0.01;
H_inv = 1./H;
H_inv(abs(H) < thresh) = 0;
g_inv = real(ifft2(ifftshift(F_shift .* H_inv)));

% 维纳滤波（正则化参数 K）
K = 0.001;
H_wiener = conj(H) ./ (abs(H).^2 + K);
g_wiener = real(ifft2(ifftshift(F_shift .* H_wiener)));

figure;
subplot(1,3,1); imshow(img,[]); title('退化图像');
subplot(1,3,2); imshow(g_inv,[]); title('逆滤波复原');
subplot(1,3,3); imshow(g_wiener,[]); title('维纳滤波复原');