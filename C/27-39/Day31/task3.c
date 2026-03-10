#include <stdio.h>

int main() {
    int x[2][4] = {{1, 9, 8, 4}, {2, 0, 4, 9}};
    int i, j;
    int *ptr1;     // 指针变量，存放int类型数据的地址
    int(*ptr2)[4]; // 指针变量，指向包含4个int元素的一维数组

    printf("输出1: 使用数组名、下标直接访问二维数组元素\n");
    for (i = 0; i < 2; ++i) {
        for (j = 0; j < 4; ++j)
            printf("%d ", x[i][j]);
        printf("\n");
    }

    printf("\n输出2: 使用指针变量ptr1(指向元素)间接访问\n");
    for (ptr1 = &x[0][0], i = 0; ptr1 < &x[0][0] + 8; ++ptr1, ++i) {
        printf("%d ", *ptr1);

        if ((i + 1) % 4 == 0)
            printf("\n");
    }
                         
    printf("\n输出3: 使用指针变量ptr2(指向一维数组)间接访问\n");
    for (ptr2 = x; ptr2 < x + 2; ++ptr2) {
        for (j = 0; j < 4; ++j)
            printf("%d ", *(*ptr2 + j));
        printf("\n");
    }

    return 0;
}