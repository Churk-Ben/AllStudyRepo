// #include <stdio.h>

// int main()
// {
//     int n;
//     long long sum = 0, max = 2147483647, min = -2147483648;
//     scanf("%d", &n);

//     long long numbers[n];

//     for (int i = 1; i <= n; i++)
//     {
//         scanf("%lld", &numbers[i - 1]);
//     }

//     for (int i = 0; i < n; i++)
//     {
//         sum += numbers[i];
//         if (sum > max || sum < min)
//         {
//             printf("%d ", i + 1);
//             break;
//         }
//         if (i + 1 == n)
//         {
//             printf("0");
//         }
//     }

//     return 0;
// }
