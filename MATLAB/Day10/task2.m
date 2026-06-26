%% ============================================================
%  模糊图像复原：稳健维纳滤波 + 亮度通道处理 + 后去噪
%  适合运动模糊 / 轻微离焦模糊
%% ============================================================

clear; clc; close all;

%% 1. 读图
I = im2double(imread("blurred wood.bmp"));

isColor = ndims(I) == 3;

if isColor
    I_ycbcr = rgb2ycbcr(I);
    Y  = I_ycbcr(:,:,1);
    Cb = I_ycbcr(:,:,2);
    Cr = I_ycbcr(:,:,3);
else
    Y = I;
end

%% 2. 参数区
% 模糊类型：'motion' 或 'gaussian'
psfType = 'motion';

% 运动模糊参数
motionLen = 2;       % 模糊长度，越大复原越强，但越容易出噪
motionTheta = 10;      % 模糊角度，单位：度

% 高斯离焦模糊参数
gaussSize = 11;
gaussSigma = 2.2;

% 维纳滤波噪声信号比
% 这个值很关键：太小会像你右图那样炸噪声；太大则复原不明显
NSR = 0.008;

% 后处理强度
bilatDegree = 0.035;
bilatSigma = 3.0;
guidedDegree = 0.0008;

%% 3. 构造 PSF 模糊核
switch lower(psfType)
    case 'motion'
        PSF = fspecial('motion', motionLen, motionTheta);
    case 'gaussian'
        PSF = fspecial('gaussian', gaussSize, gaussSigma);
    otherwise
        error('psfType 只能是 motion 或 gaussian');
end

%% 4. 边界预处理，减少维纳滤波边缘振铃
Y_taper = edgetaper(Y, PSF);

%% 5. 维纳滤波复原
Y_wiener = deconvwnr(Y_taper, PSF, NSR);
Y_wiener = clip01(Y_wiener);

%% 6. 后去噪：双边 + 导向滤波
% 先用双边滤波压掉复原产生的颗粒
try
    Y_bilat = imbilatfilt(Y_wiener, bilatDegree, bilatSigma);
catch
    Y_bilat = imgaussfilt(Y_wiener, 0.45);
end
Y_bilat = clip01(Y_bilat);

% 再用导向滤波保边，避免全图发糊
try
    Y_guided = imguidedfilter(Y_bilat, Y_wiener, ...
        'NeighborhoodSize', [5 5], ...
        'DegreeOfSmoothing', guidedDegree);
catch
    Y_guided = Y_bilat;
end
Y_guided = clip01(Y_guided);

%% 7. 轻锐化，补一点边缘
try
    Y_sharp = imsharpen(Y_guided, ...
        'Radius', 0.6, ...
        'Amount', 0.35, ...
        'Threshold', 0.03);
catch
    Y_sharp = Y_guided;
end
Y_sharp = clip01(Y_sharp);

%% 8. 混合，避免复原痕迹太重
restoreStrength = 0.80;

Y_final = restoreStrength * Y_sharp + ...
          (1 - restoreStrength) * Y;

Y_final = clip01(Y_final);

%% 9. 颜色重建
if isColor
    % 色度通道只做轻微平滑，不做反卷积，避免彩色噪点爆炸
    Cb = imgaussfilt(Cb, 0.45);
    Cr = imgaussfilt(Cr, 0.45);

    I_out_ycbcr = cat(3, Y_final, Cb, Cr);
    I_out = ycbcr2rgb(I_out_ycbcr);
else
    I_out = Y_final;
end

I_out = clip01(I_out);

%% 10. 显示结果
figure('Name', '模糊图像复原', 'Color', [0.12 0.12 0.12]);

subplot(1,3,1);
imshow(I, []);
title('模糊图像');

subplot(1,3,2);
imshow(Y_wiener, []);
title('维纳滤波复原');

subplot(1,3,3);
imshow(I_out, []);
title('最终结果');

%% 11. 保存
imwrite(I_out, 'deblur_final.png');
fprintf('已保存：deblur_final.png\n');

%% 12. 工具函数
function I = clip01(I)
    I = min(max(I, 0), 1);
end