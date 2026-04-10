Cameraman = imread("Fig0222(b)(cameraman).tif");

[height, width] = size(Cameraman);
start_row = round(height / 3);
end_row = round(height / 3 * 2);
start_col = round( width / 3);
end_col =round( width / 3 * 2);

Cameraman_bmp = Cameraman;
Cameraman_bmp(start_row:end_row, start_col:end_col) = 2 * Cameraman_bmp(start_row:end_row, start_col:end_col);

subplot(1,2,1)
imshow(Cameraman)
subplot(1,2,2)
imshow(Cameraman_bmp)

imwrite(Cameraman_bmp,".\output\cameraman_1.bmp","bmp")