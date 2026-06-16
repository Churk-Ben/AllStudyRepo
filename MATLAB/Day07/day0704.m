img = im2double(imread('Fig1051(a)(defective_weld).tif'));

% 种子点（手动指定）
seed = [100, 100];
T = 0.1;   % 生长阈值

[M, N] = size(img);
region = false(M, N);
region(seed(1), seed(2)) = true;

% 以种子点初始灰度为参考（固定均值，避免漂移）
ref_val = img(seed(1), seed(2));

stack = seed;
while ~isempty(stack)
    % 取出一个点
    p = stack(1,:);
    stack(1,:) = [];
    % 8邻域探索
    for dx = -1:1
        for dy = -1:1
            nx = p(1) + dx; ny = p(2) + dy;
            if nx>=1 && nx<=M && ny>=1 && ny<=N && ~region(nx, ny)
                if abs(img(nx, ny) - ref_val) < T
                    region(nx, ny) = true;
                    stack = [stack; nx, ny];  %#ok
                end
            end
        end
    end
end

figure;
subplot(1,2,1); imshow(img,[]);     title('原图');
subplot(1,2,2); imshow(region,[]);  title('区域生长分割结果');