function log_exp_transform_demo()
    % 读取或创建测试图像
    img = imread('cameraman.tif');  % MATLAB自带测试图
    % 如果没有该图像，使用: img = uint8(255*rand(256,256));
    
    img = im2double(img);  % 归一化到 [0,1]
    
    %% ========== 对数变换 ==========
    % 公式: s = c * log(1 + r)
    c_log = 1 / log(1 + max(img(:)));  % 归一化系数
    img_log = c_log * log(1 + img);
    
    %% ========== 指数变换 ==========
    % 公式: s = c * r^gamma
    
    % gamma < 1: 扩展低灰度区域（类似对数效果）
    gamma1 = 0.5;
    c_exp1 = 1 / (max(img(:))^gamma1);  % 归一化
    img_exp_low = c_exp1 * (img .^ gamma1);
    
    % gamma > 1: 扩展高灰度区域
    gamma2 = 2.0;
    c_exp2 = 1 / (max(img(:))^gamma2);
    img_exp_high = c_exp2 * (img .^ gamma2);
    
    %% ========== 可视化 ==========
    figure('Name', '灰度对数变换与指数变换', 'Position', [100 100 1200 800]);
    
    % 显示图像
    subplot(3, 3, 1), imshow(img), title('原始图像');
    subplot(3, 3, 2), imshow(img_log), title('对数变换');
    subplot(3, 3, 3), imhist(img), title('原始直方图');
    
    subplot(3, 3, 4), imshow(img_exp_low), title('指数变换 \gamma=0.5');
    subplot(3, 3, 5), imshow(img_exp_high), title('指数变换 \gamma=2.0');
    subplot(3, 3, 6), imhist(img_log), title('对数变换直方图');
    
    % 绘制变换曲线
    r = linspace(0, 1, 256);
    
    subplot(3, 3, 7);
    plot(r, c_log * log(1 + r), 'b-', 'LineWidth', 2);
    hold on;
    plot([0 1], [0 1], 'k--');
    xlabel('输入灰度 r'), ylabel('输出灰度 s');
    title('对数变换曲线'), grid on, axis equal;
    
    subplot(3, 3, 8);
    c_demo = 1;  % 不归一化，显示曲线形状
    plot(r, c_demo * r.^0.5, 'g-', 'LineWidth', 2); hold on;
    plot(r, c_demo * r.^2.0, 'r-', 'LineWidth', 2);
    plot([0 1], [0 1], 'k--');
    legend('\gamma=0.5', '\gamma=2.0', '恒等变换');
    xlabel('输入灰度 r'), ylabel('输出灰度 s');
    title('指数变换曲线'), grid on, axis equal;
    
    subplot(3, 3, 9);
    imhist(img_exp_low), title('指数\gamma=0.5直方图');
    
    %% ========== 保存结果（可选）==========
    % 转回 uint8 保存
    imwrite(im2uint8(img_log), 'log_transformed.png');
    imwrite(im2uint8(img_exp_low), 'exp_gamma0.5.png');
    imwrite(im2uint8(img_exp_high), 'exp_gamma2.0.png');
    
    fprintf('变换完成！\n');
    fprintf('对数变换: 扩展了 %.1f%% 的暗部灰度级\n', ...
        sum(img(:) < 0.3)/numel(img)*100);
end
