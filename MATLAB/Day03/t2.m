I = im2double(imread("Fig0507(b)(ckt-board-gauss-var-400).tif"));

sigma_spatial = 3;    
sigma_intensity = 0.1; 
gauss_template = 5;   
gauss_sigma = 1;      

h_gauss = fspecial('gaussian', gauss_template, gauss_sigma);
I_gauss = imfilter(I, h_gauss, 'replicate');

I_bilat = zeros(size(I));
[M, N] = size(I);
half_win = ceil(3 * sigma_spatial);
pad_img = padarray(I, [half_win half_win], 'replicate');

for i = 1:M
    for j = 1:N
        x = i + half_win;
        y = j + half_win;
        win = pad_img(x-half_win:x+half_win, y-half_win:y+half_win);  
        [dx, dy] = meshgrid(-half_win:half_win, -half_win:half_win);
        spatial = exp(-(dx.^2 + dy.^2) / (2 * sigma_spatial^2));
        
        intensity = exp(-(win - pad_img(x,y)).^2 / (2 * sigma_intensity^2));
     
        weights = spatial .* intensity;
        weights = weights / sum(weights(:));
        
        I_bilat(i,j) = sum(sum(win .* weights));
    end
end

figure('Name','双边滤波 vs 高斯滤波');
subplot(1,3,1); imshow(I); title('噪声原图');
subplot(1,3,2); imshow(I_gauss); title('高斯滤波 5x5');
subplot(1,3,3); imshow(I_bilat); title('双边滤波');
