#include <stdio.h>
#define N 4
#define M 2

void test1() {
    int x[N] = {1, 9, 8, 4};          
    int i;

    // �������xռ�õ��ڴ��ֽ���
    printf("sizeof(x) = %d\n", sizeof(x));

    // ���ÿ��Ԫ�صĵ�ַ��ֵ 
    for (i = 0; i < N; ++i)
        printf("%p: %d\n", &x[i], x[i]);

    // ���������x��Ӧ��ֵ 
	printf("x = %p\n", x); 
}

void test2() {
    int x[M][N] = {{1, 9, 8, 4}, {2, 0, 4, 9}};
    int i, j;

    // �����ά����xռ�õ��ڴ��ֽ���
    printf("sizeof(x) = %d\n", sizeof(x));

    // ���ÿ��Ԫ�صĵ�ַ��ֵ 
    for (i = 0; i < M; ++i)
        for (j = 0; j < N; ++j)
            printf("%p: %d\n", &x[i][j], x[i][j]);
    printf("\n");

    // �����ά������x, �Լ���x[0], x[1]��ֵ
    printf("x = %p\n", x);
    printf("x[0] = %p\n", x[0]);
    printf("x[1] = %p\n", x[1]);
    printf("\n");
}

int main() {
    printf("����1: int��һά����\n");
    test1();

    printf("\n����2: int�Ͷ�ά����\n");
    test2();

    return 0;
}