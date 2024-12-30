#include <stdio.h>
#define N 100

// ��������
void input(int x[], int n);
double compute(int x[], int n);

int main() {
    int x[N];
    int n, i;
    double ans;

    while(printf("Enter n: "), scanf("%d", &n) != EOF) {
        input(x, n);            // ��������
        ans = compute(x, n);    // ��������
        printf("ans = %.2f\n\n", ans);
    }

    return 0;
}

// ��������
void input(int x[], int n) {
    int i;

    for(i = 0; i < n; ++i)
        scanf("%d", &x[i]);
}

// ��������
double compute(int x[], int n) {
    int i, high, low;
    double ans;

    high = low = x[0];
    ans = 0;

    for(i = 0; i < n; ++i) {
        ans += x[i];

        if(x[i] > high)
            high = x[i];
        else if(x[i] < low)
            low = x[i];
    }

    ans = (ans - high - low)/(n-2);

    return ans;
}