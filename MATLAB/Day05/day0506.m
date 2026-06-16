img = im2double(imread('Fig0333(a)(test_pattern_blurring_orig).tif'));
[M,N] = size(img);

% 添加周期噪声（频率16周期/图像宽度）
[x,y] = meshgrid(1:N, 1:M);
noise = 0.1 * (sin(16*2*pi*x/N) + sin(16*2*pi*y/M));
img_noisy = min(max(img + noise, 0), 1);

F_shift = fftshift(fft2(img_noisy));
amp = log(1 + abs(F_shift));

% 噪声在频谱中的位置：u = ±16, v = ±16（中心化后）
u0 = 16; v0 = 16;
D0 = 10;   % 带阻半径
W  = 5;    % 带宽

[U,V] = meshgrid(-N/2:N/2-1, -M/2:M/2-1);
% 四个噪声点
D1 = sqrt((U-u0).^2 + (V-v0).^2);
D2 = sqrt((U+u0).^2 + (V-v0).^2);
D3 = sqrt((U-u0).^2 + (V+v0).^2);
D4 = sqrt((U+u0).^2 + (V+v0).^2);

% 高斯带阻滤波器（乘积形式，避免过度衰减通带）
H_br = (1 - exp(-((D1.^2 - D0^2)./(D1*W)).^2)) .* ...
       (1 - exp(-((D2.^2 - D0^2)./(D2*W)).^2)) .* ...
       (1 - exp(-((D3.^2 - D0^2)./(D3*W)).^2)) .* ...
       (1 - exp(-((D4.^2 - D0^2)./(D4*W)).^2));
% 避免分母为0
H_br(isnan(H_br)) = 1;

% 滤波
G = F_shift .* H_br;
out = real(ifft2(ifftshift(G)));

figure;
subplot(2,2,1); imshow(img,[]);        title('原图');
subplot(2,2,2); imshow(img_noisy,[]);  title('加周期噪声');
subplot(2,2,3); imshow(amp,[]);        title('噪声频谱（尖峰明显）');
subplot(2,2,4); imshow(out,[]);        title('带阻滤波结果');