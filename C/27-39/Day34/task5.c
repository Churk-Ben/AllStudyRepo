#include <stdio.h>
#include <math.h>// 我在这里偷偷用了个math库

typedef struct
{
    int year;
    int month;
    int day;
} Date;

// 函数声明
void input(Date *pd);                // 输入日期给pd指向的Date变量
int day_of_year(Date d);             // 返回日期d是这一年的第多少天
int compare_dates(Date d1, Date d2); // 比较两个日期:
                                     // 如果d1在d2之前，返回-1;
                                     // 如果d1在d2之后，返回1
                                     // 如果d1和d2相同，返回0

void test1()
{
    Date d;
    int i;

    printf("输入日期:(以形如2024-12-16这样的形式输入)\n");
    for (i = 0; i < 3; ++i)
    {
        input(&d);
        printf("%d-%02d-%02d是这一年中第%d天\n\n", d.year, d.month, d.day, day_of_year(d));
    }
}

void test2()
{
    Date Churk_birth, Chloris_birth;
    int i;
    int ans;

    printf("输入Churk和Chloris出生日期:(以形如2024-12-16这样的形式输入)\n");
    for (i = 0; i < 3; ++i)
    {
        input(&Churk_birth);
        input(&Chloris_birth);
        ans = compare_dates(Churk_birth, Chloris_birth);

        if (ans == 0)
            printf("Churk和Chloris一样大\n\n");
        else if (ans == -1)
            printf("Churk比Chloris大\n\n");
        else
            printf("Churk比Chloris小\n\n");
    }
}

int main()
{
    printf("测试1: 输入日期, 打印输出这是一年中第多少天\n");
    test1();

    printf("\n测试2: 两个人年龄大小关系\n");
    test2();
}

// 补足函数input实现
// 功能: 输入日期给pd指向的Date变量
void input(Date *pd)
{
    scanf("%d-%d-%d", &pd->year, &pd->month, &pd->day);
}

// 补足函数day_of_year实现
// 功能：返回日期d是这一年的第多少天
int day_of_year(Date d)
{
    int days_of_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days = 0;

    if ((d.year % 4 == 0 && d.year % 100 != 0) || d.year % 400 == 0)
        days_of_month[1]++;

    for (int i = 1; i < d.month; i++)
        days += days_of_month[i - 1];

    days += d.day;
    return days;
}

// 补足函数compare_dates实现
// 功能：比较两个日期:
// 如果d1在d2之前，返回-1;
// 如果d1在d2之后，返回1
// 如果d1和d2相同，返回0
int compare_dates(Date d1, Date d2)// 我在这里偷偷用了个math库
{
    int cmp_year = d1.year - d2.year;
    if (cmp_year != 0)
        return cmp_year / abs(cmp_year);

    int cmp_month = d1.month - d2.month;
    if (cmp_month != 0)
        return cmp_month / abs(cmp_month);

    int cmp_day = d1.day - d2.day;
    if (cmp_day != 0)
        return cmp_day / abs(cmp_day);

    return 0;
}