#include <stdio.h>

int main() {
    int x[2][4] = {{1, 9, 8, 4}, {2, 0, 4, 9}};
    int i, j;
    int *ptr1;     // ָ����������int�������ݵĵ�ַ
    int(*ptr2)[4]; // ָ�������ָ�����4��intԪ�ص�һά����

    printf("���1: ʹ�����������±�ֱ�ӷ��ʶ�ά����Ԫ��\n");
    for (i = 0; i < 2; ++i) {
        for (j = 0; j < 4; ++j)
            printf("%d ", x[i][j]);
        printf("\n");
    }

    printf("\n���2: ʹ��ָ�����ptr1(ָ��Ԫ��)��ӷ���\n");
    for (ptr1 = &x[0][0], i = 0; ptr1 < &x[0][0] + 8; ++ptr1, ++i) {
        printf("%d ", *ptr1);

        if ((i + 1) % 4 == 0)
            printf("\n");
    }
                         
    printf("\n���3: ʹ��ָ�����ptr2(ָ��һά����)��ӷ���\n");
    for (ptr2 = x; ptr2 < x + 2; ++ptr2) {
        for (j = 0; j < 4; ++j)
            printf("%d ", *(*ptr2 + j));
        printf("\n");
    }

    return 0;
}