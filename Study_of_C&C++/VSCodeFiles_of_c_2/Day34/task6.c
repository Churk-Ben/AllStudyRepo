#include <stdio.h>
#include <string.h>

enum Role
{
    admin,
    student,
    teacher
};

typedef struct
{
    char username[20]; // 用户名
    char password[20]; // 密码
    enum Role type;    // 账户类型
} Account;

// 函数声明
void output(Account x[], int n); // 输出账户数组x中n个账户信息，其中，密码用*替代显示

int main()
{
    Account x[] = {{"A1001", "123456", student},
                   {"A1002", "123abcdef", student},
                   {"A1009", "xyz12121", student},
                   {"X1009", "9213071x", admin},
                   {"C11553", "129dfg32k", teacher},
                   {"X3005", "921kfmg917", student}};
    int n;
    n = sizeof(x) / sizeof(Account);
    output(x, n);

    return 0;
}

// 待补足的函数output()实现
// 功能：遍历输出账户数组x中n个账户信息
//      显示时，密码字段以与原密码相同字段长度的*替代显示
void output(Account x[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%-10s", x[i].username);
        for (int j = 0; j < (int)strlen(x[i].password); j++)
            printf("*");
        printf("\t");
        if (x[i].type == admin)
            printf("admin\n");
        else if (x[i].type == student)
            printf("student\n");
        else if (x[i].type == teacher)
            printf("teacher\n");
    }
}