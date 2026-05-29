I = im2double(imread("Fig0508(b)(circuit-board-salt-prob-pt1).tif"));

window_size = 3;
Q_values = [-2, -1, 0, 1, 2];

contra_harm = @(img, ws, Q) ...
    imfilter(img.^(Q+1), ones(ws), 'replicate') ./ ...
    (imfilter(img.^Q, ones(ws), 'replicate') + 1e-6);

figure('Name','逆谐波均值滤波对比');
subplot(2,3,1); imshow(I); title('原图');
idx = 2;
for Q = Q_values
    I_filtered = contra_harm(I, window_size, Q);
    subplot(2,3,idx); imshow(I_filtered); title(['Q = ', num2str(Q)]);
    idx = idx + 1;
end
