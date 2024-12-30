#include <stdio.h>
#define N 100

void dec_to_n(int x, int n); // ��������

int main() {
    int x;

    while(printf("����ʮ��������: "), scanf("%d", &x) != EOF) {
        dec_to_n(x, 2);  // ��������: ��xת���ɶ��������
        dec_to_n(x, 8);  // ��������: ��xת���ɰ˽������
        dec_to_n(x, 16); // ��������: ��xת����ʮ���������

        printf("\n");
    }

    return 0;
}

// ��������
// ����: ��ʮ������xת����n���ƣ���ӡ���
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

