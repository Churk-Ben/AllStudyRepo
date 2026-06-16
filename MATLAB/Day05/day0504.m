img = im2double(imread('Fig0333(a)(test_pattern_blurring_orig).tif'));
[M,N] = size(img);
D0 = 15;
[U,V] = meshgrid(-N/2:N/2-1, -M/2:M/2-1);
D = sqrt(U.^2 + V.^2);
F_shift = fftshift(fft2(img));

% 三种高通滤波器（避免除零）
H_ideal = double(D > D0);
H_btw   = (D./D0).^4 ./ (1 + (D./D0).^4);   % 二阶巴特沃斯高通（D=0时为0）
H_gauss = 1 - exp(-D.^2 / (2 * D0^2));

% 滤波
out_ideal = real(ifft2(ifftshift(F_shift .* H_ideal)));
out_btw   = real(ifft2(ifftshift(F_shift .* H_btw)));
out_gauss = real(ifft2(ifftshift(F_shift .* H_gauss)));

figure;
subplot(1,3,1); imshow(out_ideal,[]); title('理想高通 D0=15');
subplot(1,3,2); imshow(out_btw,[]);   title('巴特沃斯高通 D0=15');
subplot(1,3,3); imshow(out_gauss,[]); title('高斯高通 D0=15');