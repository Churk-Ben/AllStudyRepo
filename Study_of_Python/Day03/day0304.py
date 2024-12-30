def next_function(patt):
    next = [0] * len(patt)  # 初始化next数组
    i = 1  # 从第二个字符开始
    j = 0  # j指向前缀的结束位置
    while i < len(patt):
        if patt[i] == patt[j]:  # 如果字符匹配
            j += 1  # 移动前缀
            next[i] = j  # 更新next数组
            i += 1  # 移动到下一个字符
        else:
            if j > 0:  # 如果j不为0，使用next数组
                j = next[j - 1]  # 移动j到上一个前缀的位置
            else:
                next[i] = 0  # j为0，则直接设置next[i]为0
                i += 1  # 移动到下一个字符
    return next

patt = ["a", "b", "c", "a", "b"]
for i in next_function(patt):
    print(i)
