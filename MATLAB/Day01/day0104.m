Cameraman = imread("Fig0222(b)(cameraman).tif");

subplot(221); imshow(Cameraman);
subplot(222); imshow(imadjust(Cameraman,[0.2,0.8],[0,1]));
subplot(223); imshow(imadjust(Cameraman,[],[],2));
subplot(224); imshow(imadjust(Cameraman,[],[],0.5));
