function se = makeDisk(r)
try
    se = strel('disk', r);
catch
    se = strel('disk', r, 0);
end
end
