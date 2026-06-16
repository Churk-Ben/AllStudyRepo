% 读取图像（若为索引图则转换为灰度）
[img, map] = imread('seeds.png');  % 请将文件名改为实际图片名
if ~isempty(map)
    img = ind2rgb(img, map);
end
if ndims(img) == 3
    img = rgb2gray(img);
end
img = im2double(img);

% 预处理：反转（使种子变亮）、中值滤波
img_inv = imcomplement(img);
img_filt = medfilt2(img_inv, [3 3]);

% 二值化 + 去除小区域和边界区域
bw = imbinarize(img_filt, graythresh(img_filt));
bw = bwareaopen(bw, 30);       % 删除小于30像素的噪点
bw = imclearborder(bw);        % 去除接触边界的区域

% 连通分量标记与面积统计
L = bwlabel(bw, 8);
stats = regionprops(L, 'Area');

figure;
subplot(1,2,1); imshow(bw);            title('二值化结果');
subplot(1,2,2); imshow(label2rgb(L));  title('ROI彩色标记');

fprintf('===== 种子ROI面积统计 =====\n');
for i = 1:length(stats)
    fprintf('ROI %2d : %d 像素\n', i, stats(i).Area);
end