#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[20];  // 姓名
    char phone[12]; // 手机号
    int vip;        // 是否为紧急联系人，是取1；否则取0
} Contact;

int vip_cnt; // 偷偷全局了一个紧急联系人个数

// 函数声明
void set_vip_contact(Contact x[], int n, char name[]); // 设置紧急联系人
void output(Contact x[], int n);                       // 输出x中联系人信息
void display(Contact x[], int n);                      // 按联系人姓名字典序升序显示信息，紧急联系人最先显示
void sort(Contact x[], int n);                         // 按姓名字典序排序联系人信息

#define N 10
int main()
{
    Contact list[N] = {
        {"齐夏", "15510846604", 0},
        {"楚天秋", "15552933732", 0},
        {"秦丁冬", "18820725036", 0},
        {"燕知春", "18077702405", 0},
        {"乔家劲", "18038747351", 0},
        {"陈俊男", "17705843215", 0},
        {"余念安", "18853253914", 0},
        {"钱五", "15547571923", 0},
        {"周六", "18856659351", 0},
        {"宋七", "13230584477", 0},
    };

    int i;
    char name[20];

    printf("显示原始通讯录信息: \n");
    output(list, N);

    printf("\n输入要设置的紧急联系人个数: ");
    scanf("%d", &vip_cnt);

    printf("输入%d个紧急联系人姓名:\n", vip_cnt);
    for (i = 0; i < vip_cnt; ++i)
    {
        scanf("%s", name);
        set_vip_contact(list, N, name);
    }

    printf("\n显示通讯录列表:(按姓名字典序升序排列,紧急联系人最先显示)\n");
    display(list, N);

    return 0;
}

// 补足函数set_vip_contact实现
// 功能：将联系人数组x中，联系人姓名与name一样的人，设置为紧急联系人（即成员vip值设为1）
void set_vip_contact(Contact x[], int n, char name[])
{
    for (int i = 0; i < N; i++)
    {
        if (strcmp(x[i].name, name) == 0)
        {
            x[i].vip = 1;
        }
    }
}

// 补足函数display实现
// 功能: 显示联系人数组x中的联系人信息
//      按姓名字典序升序显示, 紧急联系人显示在最前面
void display(Contact x[], int n)
{
    sort(x, n);
    output(x, n);
}

void output(Contact x[], int n)
{
    int i;

    for (i = 0; i < n; ++i)
    {
        printf("%-10s%-15s", x[i].name, x[i].phone);
        if (x[i].vip)
            printf("%5s", "*");
        printf("\n");
    }
}

void sort(Contact x[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (x[i].vip < x[j].vip)
            {
                Contact temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
    }
    for (int i = 0; i < vip_cnt; i++)
    {
        for (int j = i + 1; j < vip_cnt; j++)
        {
            if (strcmp(x[i].name, x[j].name) > 0)
            {
                Contact temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
    }
    for (int i = vip_cnt; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(x[i].name, x[j].name) > 0)
            {
                Contact temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
    }
}