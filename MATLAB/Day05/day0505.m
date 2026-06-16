img = im2double(imread('Fig0333(a)(test_pattern_blurring_orig).tif'));
[M,N] = size(img);
D0 = 15;
[U,V] = meshgrid(-N/2:N/2-1, -M/2:M/2-1);
D = sqrt(U.^2 + V.^2);
F_shift = fftshift(fft2(img));

H_hp = 1 - exp(-D.^2 / (2 * D0^2));   % 高斯高通

% 高频增强：H = k + H_hp (k控制低频分量)
k = 1.2;
H_enhance = k + H_hp;
% 高频提升：H = A + H_hp (更强的低频和高频提升)
A = 1.5;
H_boost = A + H_hp;

res_enhance = real(ifft2(ifftshift(F_shift .* H_enhance)));
res_boost   = real(ifft2(ifftshift(F_shift .* H_boost)));

figure;
subplot(1,2,1); imshow(res_enhance,[]); title(sprintf('高频增强 (k=%.1f)', k));
subplot(1,2,2); imshow(res_boost,[]);   title(sprintf('高频提升 (A=%.1f)', A));