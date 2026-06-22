function result = blendByMask(I, filtered, maskSoft, strength)
alpha = repmat(max(0, min(1, maskSoft*strength)), [1 1 3]);
result = I.*(1-alpha) + filtered.*alpha;
result = max(0, min(1, result));
end
