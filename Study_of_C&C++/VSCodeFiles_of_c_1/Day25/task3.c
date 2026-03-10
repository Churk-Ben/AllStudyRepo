#include <stdio.h>
#define N 100

// 函数声明
void output(int x[][N], int n);
void init(int x[][N], int n, int value);

int main() {
    int x[N][N];
    int n, value;

    while(printf("Enter n and value: "), scanf("%d%d", &n, &value) != EOF) {
        init(x, n, value);  // 函数调用
        output(x, n);       // 函数调用
        printf("\n");
    }

    return 0;
}

// 函数定义
void output(int x[][N], int n) {
    int i, j;

    for(i = 0; i < n; ++i) {
        for(j = 0; j < n; ++j)
            printf("%d ", x[i][j]);
        printf("\n");
    }
}

// 函数定义
void init(int x[][N], int n, int value) {
    int i, j;

    for(i = 0; i < n; ++i)
        for(j = 0; j < n; ++j)
            x[i][j] = value;
}