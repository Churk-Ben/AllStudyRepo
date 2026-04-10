Fig0222_b__cameraman_ = imread("E:\Coding Projects\Programme-Learning-Repo\MATLAB\Day01\Fig0222(b)(cameraman).tif");
imshow(Fig0222_b__cameraman_)

imfinfo("Fig0222(b)(cameraman).tif")

imwrite(Fig0222_b__cameraman_,".\output\Fig0222(b)(cameraman).bmp","bmp")
Fig0222_b__cameraman__bmp = imread(".\output\Fig0222(b)(cameraman).bmp");
imshow(Fig0222_b__cameraman__bmp)