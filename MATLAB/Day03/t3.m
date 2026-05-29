img = im2double(imread("Fig0507(a)(ckt-board-orig).tif"));
noisy1 = imnoise(img, 'gaussian', 0, 0.01);
noisy2 = imnoise(img, 'gaussian', 0, 0.04);
ws = [3 5]; eps = 1e-6;

figure('Name','均值滤波去噪对比');
idx = 1;
noise_var = 0.01;
for I = {noisy1, noisy2}
    for w = ws
        h = ones(w)/w^2;
        arith = imfilter(I{1}, h, 'replicate');
        geo = exp(imfilter(log(I{1}+eps), h, 'replicate'));
        harm = 1 ./ imfilter(1./(I{1}+eps), h, 'replicate');
        
        subplot(2,8,idx); imshow(I{1}); title(['噪声方差 ' num2str(noise_var)]); idx=idx+1;
        subplot(2,8,idx); imshow(arith); title(['算术均值 ' num2str(w) 'x' num2str(w)]); idx=idx+1;
        subplot(2,8,idx); imshow(geo); title(['几何均值 ' num2str(w) 'x' num2str(w)]); idx=idx+1;
        subplot(2,8,idx); imshow(harm); title(['谐波均值 ' num2str(w) 'x' num2str(w)]); idx=idx+1;
    end
    noise_var = 0.04;
end
