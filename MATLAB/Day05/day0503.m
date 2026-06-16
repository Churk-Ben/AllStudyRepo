img = im2double(imread('Fig0333(a)(test_pattern_blurring_orig).tif'));
[M,N] = size(img);
[U,V] = meshgrid(-N/2:N/2-1, -M/2:M/2-1);
D = sqrt(U.^2 + V.^2);

% 添加两种强度的高斯噪声
noise_density = [0.005, 0.02];
D0 = 70;  % 截止频率（可根据频谱调整）
H = exp(-D.^2 / (2 * D0^2));   % 高斯低通

figure;
for k = 1:2
    img_noisy = imnoise(img, 'gaussian', 0, noise_density(k));
    F_shift = fftshift(fft2(img_noisy));
    amp = log(1 + abs(F_shift));
    denoised = real(ifft2(ifftshift(F_shift .* H)));
    
    subplot(2,3, 3*k-2); imshow(img_noisy,[]); title(sprintf('噪声方差 %.3f', noise_density(k)));
    subplot(2,3, 3*k-1); imshow(amp,[]);       title('频谱');
    subplot(2,3, 3*k);   imshow(denoised,[]);  title('高斯低通去噪');
end