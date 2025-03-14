#include <stdio.h>
#include <stdlib.h>

// 判断给定k值是否满足坏人全部死亡而好人幸存
int is_valid_k(int m, int k)
{
    int total = 2 * m; // 总人数
    int *circle = (int *)malloc(total * sizeof(int));

    for (int i = 0; i < total; i++)
    {
        circle[i] = (i < m) ? 1 : 0; // 初始化好人标记为1，坏人标记为0
    }

    int current = 0;   // 当前报数位置
    int count = total; // 当前剩余人数

    while (count > m)
    {
        int step = (k - 1) % count;         // 计算报数步长
        current = (current + step) % count; // 确定死亡位置

        if (circle[current] == 1)
        { // 如果死的是好人，k无效
            free(circle);
            return 0;
        }

        // 删除当前死亡的坏人，将后面的元素前移
        for (int i = current; i < count - 1; i++)
        {
            circle[i] = circle[i + 1];
        }

        count--; // 剩余人数减少
    }

    free(circle);
    return 1; // k有效
}

int find_min_k(int m)
{
    int k = 1;
    while (!is_valid_k(m, k))
    {
        k++;
    }
    return k;
}

int main()
{
    int m;
    while (scanf("%d", &m) == 1)
    {
        int result = find_min_k(m);
        printf("%d\n", result);
    }
    return 0;
}