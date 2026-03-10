#include <stdio.h>
#define N 100

void dec_to_n(int x, int n); // 函数声明

int main() {
    int x;

    while(printf("输入十进制整数: "), scanf("%d", &x) != EOF) {
        dec_to_n(x, 2);  // 函数调用: 把x转换成二进制输出
        dec_to_n(x, 8);  // 函数调用: 把x转换成八进制输出
        dec_to_n(x, 16); // 函数调用: 把x转换成十六进制输出

        printf("\n");
    }

    return 0;
}

// 函数定义
// 功能: 把十进制数x转换成n进制，打印输出
void dec_to_n(int x, int n) {
    char ans[N];
    int i = 0;

    do {
        int t = x % n;
        ans[i++] = (t < 10) ? (t + '0') : (t - 10 + 'A');
        x /= n;
    } while (x);

    for (int j = i - 1; j >= 0; j--) {
        printf("%c",ans[j]);
    }
    printf("\n");
}

