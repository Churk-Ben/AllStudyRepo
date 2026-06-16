% 实验2：频域低通滤波对比（汇总显示）
img = im2double(imread('Fig0333(a)(test_pattern_blurring_orig).tif'));
[M,N] = size(img);
[U,V] = meshgrid(-N/2:N/2-1, -M/2:M/2-1);
D = sqrt(U.^2 + V.^2);
F_shift = fftshift(fft2(img));

D0_list = [5, 15, 30, 80, 230];

figure('Name', '低通滤波对比 (行=截止频率, 列=滤波器类型)', 'Position', [100 100 900 1200]);

for i = 1:length(D0_list)
    D0 = D0_list(i);
    
    % 三种低通滤波器
    H_ideal = double(D <= D0);
    H_btw   = 1 ./ (1 + (D./D0).^4);        % 二阶巴特沃斯
    H_gauss = exp(-(D.^2) / (2 * D0^2));    % 高斯
    
    % 滤波并还原
    out_ideal = real(ifft2(ifftshift(F_shift .* H_ideal)));
    out_btw   = real(ifft2(ifftshift(F_shift .* H_btw)));
    out_gauss = real(ifft2(ifftshift(F_shift .* H_gauss)));
    
    % 5行×3列 子图布局
    subplot(5, 3, 3*i-2);
    imshow(out_ideal, []);
    if i==1, title('理想低通'); end
    ylabel(sprintf('D_0=%d', D0));
    
    subplot(5, 3, 3*i-1);
    imshow(out_btw, []);
    if i==1, title('巴特沃斯低通'); end
    
    subplot(5, 3, 3*i);
    imshow(out_gauss, []);
    if i==1, title('高斯低通'); end
end
sgtitle('频域低通滤波对比 (行: 不同截止频率, 列: 不同滤波器)');