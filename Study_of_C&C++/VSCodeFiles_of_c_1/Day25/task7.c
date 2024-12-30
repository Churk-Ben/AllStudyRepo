#include <stdio.h>
#define N 100

// ��������
void input(int x[][N], int n);
void output(int x[][N], int n);
// �����㺯��is_magic����
int is_magic(int x[][N], int n);

int main() {
    int x[N][N];
    int n;

    while(printf("����n: "), scanf("%d", &n) != EOF) {
        printf("���뷽��:\n");  
        input(x, n); 

        printf("�������:\n");  
        output(x, n);   

        if(is_magic(x, n))
            printf("��ħ������\n\n");
        else
            printf("����ħ������\n\n");
    }

    return 0;
}

// ��������
// ����: ����һ��n*n�ľ���x
void input(int x[][N], int n) {
    int i, j;
    
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j)
            scanf("%d", &x[i][j]);
    }
}

// ����: ���һ��n*n�ľ���x
void output(int x[][N], int n) {
    int i, j;

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j)
            printf("%4d", x[i][j]);

        printf("\n");
    }
}


// ����: �ж�һ��n�׷����Ƿ�Ϊħ����������ǣ�����1�����򣬷���0
// �����㺯��is_magic����
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
