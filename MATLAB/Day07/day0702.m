img = im2double(imread('rice.png'));

% 全局迭代阈值法
T = mean(img(:));
while true
    region1 = img(img < T);
    region2 = img(img >= T);
    if isempty(region1) || isempty(region2)
        break;
    end
    T_new = (mean(region1) + mean(region2)) / 2;
    if abs(T_new - T) < 1e-4
        break;
    end
    T = T_new;
end
bw_iter = img > T;

% OTSU法
T_otsu = graythresh(img);
bw_otsu = imbinarize(img, T_otsu);

figure;
subplot(1,3,1); imshow(img,[]);       title('原图');
subplot(1,3,2); imshow(bw_iter,[]);   title(sprintf('迭代法 T=%.3f', T));
subplot(1,3,3); imshow(bw_otsu,[]);   title(sprintf('OTSU法 T=%.3f', T_otsu));