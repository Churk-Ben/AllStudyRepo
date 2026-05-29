I = im2double(imread("Fig0507(b)(ckt-board-gauss-var-400).tif"));

template_sizes = [3, 5, 7];
sigmas = [0.5, 1, 2];

figure('Name','高斯滤波器系数');
idx = 1;
for s = template_sizes
    for sg = sigmas
        h = fspecial('gaussian', s, sg);
        subplot(3, 3, idx);
        surf(h);
        title(['模板 ', num2str(s), 'x', num2str(s), ', \sigma=', num2str(sg)]);
        idx = idx + 1;
    end
end

figure('Name','高斯滤波效果对比');
idx = 1;
for s = template_sizes
    for sg = sigmas
        h = fspecial('gaussian', s, sg);
        I_filtered = imfilter(I, h, 'replicate');
        subplot(3, 3, idx);
        imshow(I_filtered);
        title(['模板 ', num2str(s), 'x', num2str(s), ', \sigma=', num2str(sg)]);
        idx = idx + 1;
    end
end
