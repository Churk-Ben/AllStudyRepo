#include <stdio.h>
#include <string.h>

int main()
{
    char ms[100], ps[100];
    fgets(ms, sizeof(ms), stdin);
    fgets(ps, sizeof(ps), stdin);

    // 去掉换行符
    ms[strcspn(ms, "\n")] = '\0';
    ps[strcspn(ps, "\n")] = '\0';

    int j = 0, index[100];
    int msL = strlen(ms);
    int psL = strlen(ps);

    // 如果主字符串长度小于模式字符串长度，直接返回
    if (msL < psL) {
        printf("Index of pattern in main string are: None\n");
        return 0;
    }

    for (int i = 0; i <= msL - psL; ) // 外层循环不增加 i，而是由内层决定
    {
        // 每次匹配前重置 t
        int t = 0;
        while (t < psL && ms[i + t] == ps[t])
        {
            t++;
        }
        
        // 如果模式串完全匹配
        if (t == psL)
        {
            index[j] = i; // 记录匹配的起始索引
            j++;

            // 直接跳过已经找到的匹配部分
            i += t; // 更新i，跳过当前匹配的字符
        }
        else
        {
            i++; // 如果没有匹配成功, 移动 i 继续查找
        }
    }

    printf("Index of pattern in main string are: ");
    if (j > 0) {
        for (int i = 0; i < j; i++)
        {
            printf("%d ", index[i]);
        }
    } else {
        printf("None"); // 如果没有找到匹配
    }
    
    printf("\n"); // 添加换行符以美化输出

    return 0;
}
