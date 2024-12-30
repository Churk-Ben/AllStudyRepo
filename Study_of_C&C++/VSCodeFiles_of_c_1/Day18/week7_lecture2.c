// 备用代码1
// #include <stdio.h>

// int fac(int n)
// {
//     if (n == 0)
//         return 1;
//     else
//         return n * fac(n - 1);
// } // 函数声明

// int main()
// {
//     int n, ans;
//     while (scanf("%d", &n) != EOF)
//     {
//         ans = fac(n); // 函数调用
//         printf("%d\n", ans);
//     }

//     return 0;
// }

// 函数定义

// //////////////////////////////////////////////
// 备用代码2
#include <stdio.h>
int fibo(int n){
    if (n==2||n==1)
    {
        return 1;
    }
    else
    {
        return fibo(n-1)+fibo(n-2);
    }
    
}   // 函数声明

int main() {
    int n;

    while(scanf("%d", &n) != EOF) {
        printf("%d\n\n", fibo(n));    // 函数调用
    }

    return 0;
}

// 函数定义

// /////////////////////////////////////////////
// // 备用代码3
// #include <stdio.h>
// double mypow(int x, int y);   // 函数声明

// int main() {
//     int x, y;
//     double ans;

//     while(scanf("%d%d", &x, &y) != EOF) {
//         ans = mypow(x, y);    // 函数调用
//         printf("%d的%d次方: %g\n\n", x, y, ans);
//     }

//     return 0;
// }

// // 函数定义