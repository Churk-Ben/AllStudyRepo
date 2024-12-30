/*
某校计算机专业《程序设计基础》课程的期末总评成绩按平时表现10%、课程作业20%、课程实验10%、期末考试60%计算。
学生信息包括：学号、姓名、平时成绩、作业成绩、实验成绩、期末考试成绩、总评成绩和成绩等级。
fun函数的功能是：计算每名学生的总评成绩，将总评成绩大于等于90的学生成绩等级设置为"优秀"、大于等于80而小于90的学生成绩等级设置为"良好"、大于等于70而小于80的学生成绩等级设置为"中等"、大于等于60而小于70的学生成绩等级设置为"及格"、小于60的学生成绩等级设置为"不及格"。同时将等级为“优秀”的学生信息保存在数组h中，并返回优秀等级的学生人数。
主函数中输入n名学生的学号、姓名以及各单项成绩（百分制），调用fun函数，并输出所有优秀等级的学生信息。
程序运行时，若依次输入：
6
101 B1 100 100 100 84
102 B2 100 100 100 34
103 G1 95 95 90 95
104 B3 80 58 52 80
105 G2 85 80 85 80
106 B4 10 10 10 91
则输出结果为：
优秀等级人数: 2
 101  B1  90  优秀
 103  G1  95  优秀
注意：部分源程序已给出，请勿改动main函数和其他已有的任何内容，仅在注释“Begin”和“End”之间填入所编写的若干语句。
试题程序：
*/
#include <stdio.h>
#include <string.h>
#define N 100

typedef struct
{
    int num;       /*学号*/
    char name[16]; /*姓名*/
    int s1;        /*平时成绩*/
    int s2;        /*作业成绩*/
    int s3;        /*实验成绩*/
    int s4;        /*期末考试成绩*/
    double score;  /*总评成绩*/
    char level[8]; /*成绩等级*/
} STUREC;

int fun(STUREC st[], STUREC h[], int n)
{
    /***********Begin*********/
    int count = 0; // 优秀学生的数量

    for (int i = 0; i < n; i++)
    {
        // 计算总评成绩
        st[i].score = st[i].s1 * 0.1 + st[i].s2 * 0.2 + st[i].s3 * 0.1 + st[i].s4 * 0.6;

        // 根据总评成绩设置成绩等级
        if (st[i].score >= 90)
        {
            strcpy(st[i].level, "优秀");
            h[count++] = st[i]; // 将优秀学生的信息存入数组 h
        }
        else if (st[i].score >= 80)
        {
            strcpy(st[i].level, "良好");
        }
        else if (st[i].score >= 70)
        {
            strcpy(st[i].level, "中等");
        }
        else if (st[i].score >= 60)
        {
            strcpy(st[i].level, "及格");
        }
        else
        {
            strcpy(st[i].level, "不及格");
        }
    }

    return count; // 返回优秀学生的数量
    /***********End***********/
}

int main()
{
    STUREC s[N], h[N];
    int i, n, k;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d%s%d%d%d%d", &s[i].num, s[i].name, &s[i].s1, &s[i].s2, &s[i].s3, &s[i].s4);

    k = fun(s, h, n);

    printf("优秀等级人数: %d\n", k);
    for (i = 0; i < k; i++)
        printf("%4d%4s%4.0lf%6s\n", h[i].num, h[i].name, h[i].score, h[i].level);

    return 0;
}