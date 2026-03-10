#include <stdio.h>
#define N 100

// 函数声明
void input(int x[][N], int n);
void output(int x[][N], int n);
// 待补足函数is_magic声明
int is_magic(int x[][N], int n);

int main() {
    int x[N][N];
    int n;

    while(printf("输入n: "), scanf("%d", &n) != EOF) {
        printf("输入方阵:\n");  
        input(x, n); 

        printf("输出方阵:\n");  
        output(x, n);   

        if(is_magic(x, n))
            printf("是魔方矩阵\n\n");
        else
            printf("不是魔方矩阵\n\n");
    }

    return 0;
}

// 函数定义
// 功能: 输入一个n*n的矩阵x
void input(int x[][N], int n) {
    int i, j;
    
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j)
            scanf("%d", &x[i][j]);
    }
}

// 功能: 输出一个n*n的矩阵x
void output(int x[][N], int n) {
    int i, j;

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j)
            printf("%4d", x[i][j]);

        printf("\n");
    }
}


// 功能: 判断一个n阶方阵是否为魔方矩阵，如果是，返回1，否则，返回0
// 待补足函数is_magic定义
int is_magic(int x[][N], int n) {
    int sum = 0, temp;

    for (int j = 0; j < n; ++j)
        sum += x[0][j];

    for (int i = 1; i < n; ++i) {
        temp = 0;
        for (int j = 0; j < n; ++j)
            temp += x[i][j];
        if (temp != sum)
            return 0;
    }

    for (int j = 0; j < n; ++j) {
        temp = 0;
        for (int i = 0; i < n; ++i)
            temp += x[i][j];
        if (temp != sum)
            return 0;
    }

    temp = 0;
    for (int i = 0; i < n; ++i)
        temp += x[i][i];
    if (temp != sum)
        return 0;

    temp = 0;
    for (int i = 0; i < n; ++i)
        temp += x[i][n - i - 1];
    if (temp != sum)
        return 0;

    return 1;
}
