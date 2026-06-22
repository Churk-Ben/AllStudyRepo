function [lipMask, cheekMask] = detectFeatures_1(img, skinMask)
% DETECTFEATURES_1  五官定位 (借鉴 Day09 唇部 + 眼部估计布局)
%   1. 从皮肤掩膜估算人脸边界框
%   2. 在脸部上半区寻找双瞳暗区 → 计算眼连线
%   3. 面颊中心 = 眼连线向下平移
%   4. 唇部: 面部下半区的红色分量优势 + ROI
%
%   [lipMask, cheekMask] = detectFeatures_1(img, skinMask)
%
%   输入:
%       img       - HxWx3 double 原图 [0,1]
%       skinMask  - HxW double 皮肤软掩膜 [0,1]
%   输出:
%       lipMask   - HxW double 唇部软掩膜 [0,1]
%       cheekMask - HxW double 面颊软掩膜 [0,1]

    [h, w, ~] = size(img);

    % ========== 人脸边界框估算 ==========
    [rows, cols] = find(skinMask > 0.25);
    if isempty(rows)
        lipMask   = zeros(h, w);
        cheekMask = zeros(h, w);
        fprintf('[detectFeatures_1] No skin region found.\n');
        return;
    end

    rowMin  = max(1,      min(rows));
    rowMax  = min(h,      max(rows));
    colMin  = max(1,      min(cols));
    colMax  = min(w,      max(cols));
    faceH   = rowMax - rowMin;
    faceW   = colMax - colMin;
    cx      = (colMin + colMax) / 2;

    % ========== 眼部估计 (暗色区域) ==========
    % 搜索范围: 脸部上方 20%~45% 高度
    eyeTop    = max(1,      round(rowMin + faceH * 0.20));
    eyeBot    = min(h,      round(rowMin + faceH * 0.45));
    eyeLeft   = max(1,      round(cx - faceW * 0.25));
    eyeRight  = min(w,      round(cx + faceW * 0.25));

    % HSV 只用一次
    hsvImg = rgb2hsv(img);

    % 在 HSV 中用 1-V 表示暗度, 叠加皮肤掩膜约束
    darkness = (1 - hsvImg(:,:,3)) .* skinMask;

    % 仅在眼部 ROI 内寻找
    eyeCrop = darkness(eyeTop:eyeBot, eyeLeft:eyeRight);
    threshold = 0.45;   % 暗度阈值
    eyeBin = eyeCrop > threshold;
    eyeBin = bwareaopen(eyeBin, 50);

    % 连通域分析 → 找两个最显著的眼部暗区
    CC = bwconncomp(eyeBin);
    stats = regionprops(CC, 'Centroid', 'Area');
    if length(stats) < 2
        % 降级: 按面部比例硬估眼位
        leftEyeX  = cx - faceW * 0.14;
        leftEyeY  = rowMin + faceH * 0.32;
        rightEyeX = cx + faceW * 0.14;
        rightEyeY = leftEyeY;
    else
        areas = [stats.Area];
        [~, order] = sort(areas, 'descend');
        centroids = cat(1, stats(order(1:min(2,end))).Centroid);
        if size(centroids, 1) >= 2
            leftPt  = centroids(1,:);
            rightPt = centroids(2,:);
            if leftPt(1) > rightPt(1)
                tmp = leftPt; leftPt = rightPt; rightPt = tmp;
            end
            leftEyeX  = eyeLeft - 1 + leftPt(1);
            leftEyeY  = eyeTop  - 1 + leftPt(2);
            rightEyeX = eyeLeft - 1 + rightPt(1);
            rightEyeY = eyeTop  - 1 + rightPt(2);
        else
            leftEyeX  = cx - faceW * 0.14;
            leftEyeY  = rowMin + faceH * 0.32;
            rightEyeX = cx + faceW * 0.14;
            rightEyeY = leftEyeY;
        end
    end

    eyeMidY = (leftEyeY + rightEyeY) / 2;
    fprintf('[detectFeatures_1] Eyes: (%.0f,%.0f) / (%.0f,%.0f)\n', ...
            leftEyeX, leftEyeY, rightEyeX, rightEyeY);

    % ========== 面颊: 眼连线向下平移 ==========
    % 平移量 = 眼到下脸颊中心的距离 (约 faceH * 0.24)
    cheekCY = round(eyeMidY + faceH * 0.24);
    % 水平偏移: 两侧各移出眼宽的 ~50%
    eyeDist = abs(rightEyeX - leftEyeX);
    if eyeDist < 20, eyeDist = faceW * 0.28; end
    leftCX  = round(leftEyeX  - eyeDist * 0.28);
    rightCX = round(rightEyeX + eyeDist * 0.28);

    rx = round(eyeDist * 0.32);      % 椭圆半长轴
    ry = round(faceH   * 0.08);      % 椭圆半短轴

    [X, Y] = meshgrid(1:w, 1:h);
    leftDist  = ((X - leftCX)  / rx).^2 + ((Y - cheekCY) / ry).^2;
    rightDist = ((X - rightCX) / rx).^2 + ((Y - cheekCY) / ry).^2;

    leftSoft  = exp(-leftDist  * 3.5);
    rightSoft = exp(-rightDist * 3.5);
    cheekSoft = max(leftSoft, rightSoft);

    cheekMask = cheekSoft .* skinMask;
    cheekMask(cheekMask < 0.12) = 0;
    if max(cheekMask(:)) > 0
        cheekMask = cheekMask / max(cheekMask(:));
    end

    % ========== 唇部检测 (Day09 风格) ==========
    R = img(:,:,1);
    G = img(:,:,2);
    B = img(:,:,3);
    redness = R - 0.5 * (G + B);

    H = hsvImg(:,:,1);
    S = hsvImg(:,:,2);
    V = hsvImg(:,:,3);

    redHue = (H <= 0.08) | (H >= 0.94);

    % 唇部 ROI: 面部下半区, 居中
    lipTop   = round(rowMin + faceH * 0.72);
    lipBot   = rowMax;
    lipLeft  = round(cx - faceW * 0.18);
    lipRight = round(cx + faceW * 0.18);

    lipROI = false(h, w);
    lipROI(max(1,lipTop):lipBot, max(1,lipLeft):min(w,lipRight)) = true;

    lipMaskBin = lipROI & redHue & (S >= 0.30) & (V >= 0.18) & ...
                 (redness >= 0.15) & (R > 1.10 * G) & (R > 1.10 * B);
    lipMaskBin = imopen(lipMaskBin,  strel('disk', 1));
    lipMaskBin = imclose(lipMaskBin, strel('disk', 2));
    lipMaskBin = bwareaopen(lipMaskBin, 15);
    if any(lipMaskBin(:))
        lipMaskBin = bwareafilt(lipMaskBin, 1);
    end

    lipMask = imgaussfilt(double(lipMaskBin), 1.5);
    if max(lipMask(:)) > 0
        lipMask = lipMask / max(lipMask(:));
    end

    fprintf('[detectFeatures_1] Lip & cheek masks generated.\n');
end
