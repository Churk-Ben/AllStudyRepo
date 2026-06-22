%% 形态学结构元素辅助函数（兼容不同MATLAB版本）
function se = makeDisk(r)
    try
        se = strel('disk', r);
    catch
        se = strel('disk', r, 0);
    end
end