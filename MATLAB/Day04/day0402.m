clear; clc; close all;

img = im2double(imread("Fig0514(a)(ckt_saltpep_prob_pt25).tif"));
[m, n] = size(img);
S0 = 3;
Smax = 7;

% 普通3×3中值
med3 = medfilt2(img, [3 3]);

% 自适应中值
pad_total = floor(Smax/2);
img_large = padarray(img, [pad_total pad_total], 'replicate');
adap_med = zeros(m, n);

for i = 1:m
    for j = 1:n
        curS = S0;
        while true
            half = floor(curS/2);
            rows = i + pad_total - half : i + pad_total + half;
            cols = j + pad_total - half : j + pad_total + half;
            block = img_large(rows, cols);
            zmin = min(block(:));
            zmax = max(block(:));
            zmed = median(block(:));
            zxy = img(i, j);
            if (zmed > zmin) && (zmed < zmax)
                if (zxy > zmin) && (zxy < zmax)
                    adap_med(i, j) = zxy;
                else
                    adap_med(i, j) = zmed;
                end
                break;
            else
                curS = curS + 2;
                if curS > Smax
                    adap_med(i, j) = zmed;
                    break;
                end
            end
        end
    end
end

figure;
subplot(1,3,1); imshow(img); title('原图');
subplot(1,3,2); imshow(med3); title('3×3中值滤波');
subplot(1,3,3); imshow(adap_med); title('自适应中值滤波');