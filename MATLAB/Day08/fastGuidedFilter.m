%% 快速引导滤波实现（Fast Guided Filter）
function q = fastGuidedFilter(I, p, r, eps, s)
    if nargin < 5
        s = 4;
    end
    I_sub = imresize(I, 1/s, 'nearest');
    p_sub = imresize(p, 1/s, 'nearest');
    r_sub = max(1, round(r / s));
    
    mean_I  = imboxfilt(I_sub, 2*r_sub+1);
    mean_p  = imboxfilt(p_sub, 2*r_sub+1);
    mean_Ip = imboxfilt(I_sub .* p_sub, 2*r_sub+1);
    mean_II = imboxfilt(I_sub .* I_sub, 2*r_sub+1);
    
    var_I  = mean_II - mean_I.^2;
    cov_Ip = mean_Ip - mean_I .* mean_p;
    
    a = cov_Ip ./ (var_I + eps);
    b = mean_p - a .* mean_I;
    
    mean_a = imboxfilt(a, 2*r_sub+1);
    mean_b = imboxfilt(b, 2*r_sub+1);
    
    mean_a_full = imresize(mean_a, size(I), 'bilinear');
    mean_b_full = imresize(mean_b, size(I), 'bilinear');
    
    q = mean_a_full .* I + mean_b_full;
end