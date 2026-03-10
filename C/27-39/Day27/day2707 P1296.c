#include <stdio.h>

int unit1[3][3] = {
    {1, 0, 1},
    {0, 1, 0},
    {1, 0, 1}
};

void printbyunit(int n) {
    if (n <= 0) return; // 如果 n <= 0，直接返回

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (unit1[i][j] == 1) {
                printf("X");
            } else {
                printf(" ");
            }
        }
        printf("\n"); // 每打印完一行后换行
    }
}

int main() {
    int n;
    scanf("%d", &n);
    printbyunit(n); // 调用函数，仅以 n 为参数
    return 0;
}
