img = im2double(imread('Fig0526(a)(original_DIP).tif'));
[M,N] = size(img);
% 频率网格（中心化）
[U,V] = meshgrid(-N/2:N/2-1, -M/2:M/2-1);
F_shift = fftshift(fft2(img));

% 参数设置：a,b 控制模糊方向/长度，T 为曝光时间
T = 1;
params = [0.02, 0; 0.04, 0.02];   % 两组(a,b)

figure;
subplot(1,3,1); imshow(img,[]); title('原图');

for i = 1:2
    a = params(i,1); b = params(i,2);
    % 运动模糊退化函数（频率域）
    H = (T ./ (pi*(U*a + V*b) + eps)) .* ...
        sin(pi*(U*a + V*b)) .* exp(-1i*pi*(U*a + V*b));
    H(U*a + V*b == 0) = T;   % 直流分量修正
    % 退化并反变换
    G = F_shift .* H;
    g = real(ifft2(ifftshift(G)));
    subplot(1,3,i+1); imshow(g,[]);
    title(sprintf('运动模糊 a=%.2f,b=%.2f', a, b));
end