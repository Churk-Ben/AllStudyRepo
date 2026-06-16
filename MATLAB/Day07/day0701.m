img = im2double(imread('Fig1016(a)(building_original).tif'));

% 8个方向 Kirsch 核
K = zeros(3,3,8);
K(:,:,1) = [-3 -3  5; -3 0  5; -3 -3  5];
K(:,:,2) = [-3  5  5; -3 0  5; -3 -3 -3];
K(:,:,3) = [ 5  5  5; -3 0 -3; -3 -3 -3];
K(:,:,4) = [ 5  5 -3;  5 0 -3; -3 -3 -3];
K(:,:,5) = [ 5 -3 -3;  5 0 -3;  5 -3 -3];
K(:,:,6) = [-3 -3 -3;  5 0 -3;  5  5 -3];
K(:,:,7) = [-3 -3 -3; -3 0 -3;  5  5  5];
K(:,:,8) = [-3 -3 -3; -3 0  5; -3  5  5];

% 计算各方向边缘响应并取最大值
edge_map = zeros(size(img));
for i = 1:8
    edge_map = max(edge_map, abs(conv2(img, K(:,:,i), 'same')));
end

% 阈值分割
T = 0.3;
edge_bin = edge_map > T;

figure;
subplot(1,3,1); imshow(img,[]);      title('原图');
subplot(1,3,2); imshow(edge_map,[]); title('Kirsch边缘强度图');
subplot(1,3,3); imshow(edge_bin,[]); title(sprintf('阈值分割 (T=%.1f)', T));