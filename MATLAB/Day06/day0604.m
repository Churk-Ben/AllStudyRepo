% 读取三幅不同噪声强度的退化图像
img1 = im2double(imread('Fig0529(a)(noisiest_var_pt1).tif'));
img2 = im2double(imread('Fig0529(d)(medium_noise_var_pt01).tif'));
img3 = im2double(imread('Fig0529(g)(least_noise_var_10minus37).tif'));

[M,N] = size(img1);
[U,V] = meshgrid(-N/2:N/2-1, -M/2:M/2-1);

% 运动模糊退化函数（已知 a=0.02, b=0, T=1）
a = 0.02; b = 0; T = 1;
H = (T ./ (pi*(U*a + V*b) + eps)) .* ...
    sin(pi*(U*a + V*b)) .* exp(-1i*pi*(U*a + V*b));
H(U*a + V*b == 0) = T;

F_shift = cell(1,3);
F_shift{1} = fftshift(fft2(img1));
F_shift{2} = fftshift(fft2(img2));
F_shift{3} = fftshift(fft2(img3));

% 维纳滤波参数
K = 0.01;

figure;
titles = {'强噪声', '中噪声', '弱噪声'};
for i = 1:3
    % 逆滤波（加阈值）
    H_inv = 1./H;
    H_inv(abs(H) < 0.01) = 0;
    g_inv = real(ifft2(ifftshift(F_shift{i} .* H_inv)));
    
    % 维纳滤波
    H_w = conj(H) ./ (abs(H).^2 + K);
    g_w = real(ifft2(ifftshift(F_shift{i} .* H_w)));
    
    subplot(2,3,i); imshow(g_inv,[]); title([titles{i} ' 逆滤波']);
    subplot(2,3,i+3); imshow(g_w,[]); title([titles{i} ' 维纳滤波']);
end
sgtitle('逆滤波 vs 维纳滤波复原对比');