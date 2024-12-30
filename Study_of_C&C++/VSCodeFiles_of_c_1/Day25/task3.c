#include <stdio.h>
#define N 100

// ��������
void output(int x[][N], int n);
void init(int x[][N], int n, int value);

int main() {
    int x[N][N];
    int n, value;

    while(printf("Enter n and value: "), scanf("%d%d", &n, &value) != EOF) {
        init(x, n, value);  // ��������
        output(x, n);       // ��������
        printf("\n");
    }

    return 0;
}

// ��������
void output(int x[][N], int n) {
    int i, j;

    for(i = 0; i < n; ++i) {
        for(j = 0; j < n; ++j)
            printf("%d ", x[i][j]);
        printf("\n");
    }
}

// ��������
void init(int x[][N], int n, int value) {
    int i, j;

    for(i = 0; i < n; ++i)
        for(j = 0; j < n; ++j)
            x[i][j] = value;
}