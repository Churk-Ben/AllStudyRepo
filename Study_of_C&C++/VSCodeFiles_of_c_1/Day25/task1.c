#include <stdio.h>
#define N 4
#define M 2

void test1() {
    int x[N] = {1, 9, 8, 4};          
    int i;

    // 输出数组x占用的内存字节数
    printf("sizeof(x) = %d\n", sizeof(x));

    // 输出每个元素的地址、值 
    for (i = 0; i < N; ++i)
        printf("%p: %d\n", &x[i], x[i]);

    // 输出数组名x对应的值 
	printf("x = %p\n", x); 
}

void test2() {
    int x[M][N] = {{1, 9, 8, 4}, {2, 0, 4, 9}};
    int i, j;

    // 输出二维数组x占用的内存字节数
    printf("sizeof(x) = %d\n", sizeof(x));

    // 输出每个元素的地址、值 
    for (i = 0; i < M; ++i)
        for (j = 0; j < N; ++j)
            printf("%p: %d\n", &x[i][j], x[i][j]);
    printf("\n");

    // 输出二维数组名x, 以及，x[0], x[1]的值
    printf("x = %p\n", x);
    printf("x[0] = %p\n", x[0]);
    printf("x[1] = %p\n", x[1]);
    printf("\n");
}

int main() {
    printf("测试1: int型一维数组\n");
    test1();

    printf("\n测试2: int型二维数组\n");
    test2();

    return 0;
}