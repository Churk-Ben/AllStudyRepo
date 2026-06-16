f1 = zeros(128,128);
f1(15:113, 38:90) = 255;          % 白色矩形块

% 旋转45度，裁剪为原尺寸
f2 = imrotate(f1, -45, 'bilinear', 'crop');

% FFT与频谱
F1 = fftshift(fft2(f1));
F2 = fftshift(fft2(f2));
amp1 = log(1 + abs(F1));
amp2 = log(1 + abs(F2));

% 显示
figure;
subplot(2,2,1); imshow(f1,[]); title('原图 f1');
subplot(2,2,2); imshow(amp1,[]); title('f1 幅度谱');
subplot(2,2,3); imshow(f2,[]); title('旋转 45° f2');
subplot(2,2,4); imshow(amp2,[]); title('f2 幅度谱');