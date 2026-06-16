clear; clc; close all;
img = im2double(imread('Fig0525(a)(aerial_view_no_turb).tif'));
[M,N] = size(img);
[U,V] = meshgrid(-N/2:N/2-1, -M/2:M/2-1);
F_shift = fftshift(fft2(img));

k_list = [0.0025, 0.004];   % 湍流强度

figure;
subplot(1,3,1); imshow(img,[]); title('原图');
for i = 1:2
    k = k_list(i);
    H = exp(-k * (U.^2 + V.^2).^(5/6));
    G = F_shift .* H;
    g = real(ifft2(ifftshift(G)));
    subplot(1,3,i+1); imshow(g,[]);
    title(sprintf('大气湍流 k=%.4f', k));
end