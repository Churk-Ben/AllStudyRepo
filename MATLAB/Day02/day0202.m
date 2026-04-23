function BW = bwGenerationSmart(img,n,bw)
    level = graythresh(img);
    hist = imhist(img);
    BW = imbinarize(img, level);

    figure
    subplot(2,2,1);
    imshow(img);

    subplot(2,2,2);
    plot(hist);
    hold on;
    xline(level*255, 'r-', 'LineWidth', 1.5);
    xline(n, 'g-', 'LineWidth', 1.5);
    legend("hist","Auto","Artificial");
    hold off;

    subplot(2,2,3);
    imshow(bw);

    subplot(2,2,4);
    imshow(BW);
    title("bw\_Otsu");
end

Eight = imread("eight.tif");
Rice = imread("rice.png");
Moon = imread("Fig0338(a)(blurry_moon).tif");

threshold = 128;
EightBin = Eight >= threshold;
RiceBin = Rice >= threshold;
MoonBin = Moon >= threshold;

EightOtsu = bwGenerationSmart(Eight,threshold,EightBin);
RiceOtsu = bwGenerationSmart(Rice,threshold,RiceBin);
MoonOtsu = bwGenerationSmart(Moon,threshold,MoonBin);


imshow(EightOtsu)
imshow(RiceOtsu)
imshow(MoonOtsu)