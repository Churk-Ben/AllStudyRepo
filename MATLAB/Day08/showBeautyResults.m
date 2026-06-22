%% 可视化辅助函数
function showBeautyResults(original, result, skinMask)
    figure('Name', '人像美颜处理结果', 'Position', [100 100 1200 400]);
    subplot(1, 3, 1); imshow(original); title('原始图像');
    subplot(1, 3, 2); imshow(result); title('美颜处理后');
    if ~isempty(skinMask)
        subplot(1, 3, 3); imshow(skinMask, []); title('皮肤检测软蒙版');
    end
end