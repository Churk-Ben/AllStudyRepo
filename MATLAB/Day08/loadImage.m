function img = loadImage(filename)
% LOADIMAGE 从 input/ 目录加载预选图片, 返回 double 类型 [0,1] 图像
%
%   img = loadImage(filename)
%
%   输入:
%       filename - input/ 下的图片文件名 (如 'portrait1.jpeg')
%   输出:
%       img      - HxWx3 的 double 图像, 值域 [0, 1]

    baseDir = fileparts(mfilename('fullpath'));
    if isempty(baseDir)
        baseDir = pwd;
    end
    inputDir = fullfile(baseDir, 'input');

    imgPath = fullfile(inputDir, filename);
    if ~isfile(imgPath)
        error('Image not found: %s', imgPath);
    end

    img = im2double(imread(imgPath));

    fprintf('[loadImage] Loaded: %s  (%.0f x %.0f)\n', filename, size(img,2), size(img,1));
end
