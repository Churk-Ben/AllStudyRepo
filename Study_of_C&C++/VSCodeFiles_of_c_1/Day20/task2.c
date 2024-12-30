#include <stdio.h>

int sum_digits(int n); // ��������

int main()
{
    int n;
    int ans;

    while (printf("Enter n: "), scanf("%d", &n) != EOF)
    {
        ans = sum_digits(n); // ��������
        printf("n = %d, ans = %d\n\n", n, ans);
    }

    return 0;
}

// ��������
int sum_digits(int n)
{
    int ans = 0;

    while (n != 0)
    {
        ans += n % 10;
        n /= 10;
    }

    return ans;
}