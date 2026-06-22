function fig = saveCompareFigure(images, titles, layoutSize, ...
    outPath, figureName, visible)
showWindow = visible && usejava('desktop');
if showWindow
    visibility = 'on';
else
    visibility = 'off';
end

fig = figure('Name', figureName, 'Color', 'w', ...
    'Visible', visibility, 'Position', [80 80 1200 720]);
tiledlayout(layoutSize(1), layoutSize(2), ...
    'TileSpacing', 'compact', 'Padding', 'compact');
for k = 1:numel(images)
    nexttile;
    if ndims(images{k}) == 2
        imshow(images{k}, []);
    else
        imshow(images{k});
    end
    title(titles{k});
end
drawnow;
exportgraphics(fig, outPath, 'Resolution', 160);
if ~showWindow
    close(fig);
end
end
