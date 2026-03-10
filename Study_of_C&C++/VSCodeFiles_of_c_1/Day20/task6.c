#include <stdio.h>

int func(int n, int m); // 函数声明

int main()
{
    int n, m;
    int ans;

    while (scanf("%d%d", &n, &m) != EOF)
    {
        if (n<m)
        {
            printf("n = %d, m = %d, ans = 0\n\n", n, m);
            continue;
        }
        
        ans = func(n, m); // 函数调用
        printf("n = %d, m = %d, ans = %d\n\n", n, m, ans);
    }

    return 0;
}

// 函数定义
int func(int n, int m)
{
    if (m == n || m == 0)
        return 1;
    else
        return func(n - 1, m) + func(n - 1, m - 1);
}

/*
int factorial(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}

int func(int n, int m)
{
    return factorial(n) / factorial(m) / factorial(n - m);
}
*/

/*
int func(int n, int m)
{
    int ans = 1;
    for (int i = 0; i < m; i++)
    {
        ans *= n--;
    }
    for (int i = 1; i <= m; i++)
    {
        ans /= i;
    }
    return ans;
}
*/