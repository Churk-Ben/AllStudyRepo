%% 皮肤掩码后处理函数
function maskSmooth = processSkinMask(skinMask)
    % 形态学开运算去除小噪声
    se1 = strel('disk', 3);
    maskOpen = imopen(skinMask, se1);
    
    % 形态学闭运算填充孔洞
    se2 = strel('disk', 5);
    maskClose = imclose(maskOpen, se2);
    
    % 高斯模糊羽化边缘（sigma=8, 核大小15x15）
    maskSmooth = imgaussfilt(maskClose, 8, 'FilterSize', 15);
end
