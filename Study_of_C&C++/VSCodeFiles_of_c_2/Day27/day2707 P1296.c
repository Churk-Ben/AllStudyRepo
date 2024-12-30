#include <stdio.h>

int unit1[3][3] = {
    {1, 0, 1},
    {0, 1, 0},
    {1, 0, 1}
};

void printbyunit(int n) {
    if (n <= 0) return; // ��� n <= 0��ֱ�ӷ���

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (unit1[i][j] == 1) {
                printf("X");
            } else {
                printf(" ");
            }
        }
        printf("\n"); // ÿ��ӡ��һ�к���
    }
}

int main() {
    int n;
    scanf("%d", &n);
    printbyunit(n); // ���ú��������� n Ϊ����
    return 0;
}
