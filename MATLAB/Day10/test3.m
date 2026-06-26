%% ============================================================
%  图像复原算法：运动模糊复原
%  适用：图1（模糊树林图像）
%% ============================================================

clear; clc; close all;

% 读取图像
I_blur = imread("blurred wood.bmp");  % 模糊图
I_blur = im2double(I_blur);

% 若为彩色，分别处理RGB通道或转灰度
if size(I_blur, 3) == 3
    % 方法1：转灰度
    % I_blur = rgb2gray(I_blur);
    
    % 方法2：分别处理每个通道（效果更好）
    I_blur_R = I_blur(:,:,1);
    I_blur_G = I_blur(:,:,2);
    I_blur_B = I_blur(:,:,3);
    
    % 对每个通道复原
    I_restored_R = restore_channel(I_blur_R);
    I_restored_G = restore_channel(I_blur_G);
    I_restored_B = restore_channel(I_blur_B);
    
    I_restored = cat(3, I_restored_R, I_restored_G, I_restored_B);
else
    I_restored = restore_channel(I_blur);
end

%% 结果显示
figure('Name', '图像复原结果');
if size(I_blur, 3) == 3
    subplot(1,2,1); imshow(I_blur); title('模糊图像');
    subplot(1,2,2); imshow(I_restored); title('维纳滤波复原');
else
    subplot(1,2,1); imshow(I_blur, []); title('模糊图像');
    subplot(1,2,2); imshow(I_restored, []); title('维纳滤波复原');
end

%% 保存结果
imwrite(I_restored, 'forest_restored.png');

%% ============================================================
%  复原函数：对单通道进行维纳滤波
%% ============================================================
function I_restored = restore_channel(I_blur)
    [M, N] = size(I_blur);
    
    %% Step 1: 估计运动模糊PSF（点扩散函数）
    % 观察模糊方向：树林图看起来是水平或略微倾斜的运动模糊
    % 参数：LEN=运动长度，THETA=运动角度（度）
    
    LEN = 3;      % 模糊长度，需要根据图像调整！
    THETA = 45;     % 模糊角度，0=水平，90=垂直，根据实际调整！
    
    PSF = fspecial('motion', LEN, THETA);
    
    %% Step 2: 使用维纳滤波复原
    % 维纳滤波公式：F(u,v) = [1/H(u,v)] * [|H|^2 / (|H|^2 + K)] * G(u,v)
    % K: 噪声与信号功率比，需要调参
    
    % 方法1：deconvwnr 自动估计
    % I_restored = deconvwnr(I_blur, PSF);
    
    % 方法2：手动指定噪声功率比（通常效果更好）
    NSR = 0.08;  % 噪声信号比，需要根据图像调整！范围：0.001~0.1
    I_restored = deconvwnr(I_blur, PSF, NSR);
    
    %% Step 3: 约束处理（防止振铃和越界）
    I_restored = max(0, min(1, I_restored));  % 裁剪到[0,1]
    
    %% 可选：Lucy-Richardson 迭代去卷积（如果维纳效果不佳）
    % I_restored = deconvlucy(I_blur, PSF, 10);
    
    %% 可选：后处理 — 去除振铃
    I_restored = edgetaper(I_restored, PSF);
    
    %% Step 4: 对比度增强
    I_restored = imadjust(I_restored, stretchlim(I_restored), []);
end