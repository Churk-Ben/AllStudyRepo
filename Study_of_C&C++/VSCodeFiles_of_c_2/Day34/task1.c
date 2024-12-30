// P286例8.17
// 对教材示例代码作了微调，把输出学生信息单独编写成一个函数模块
// 打印不及格学生信息、打印所有学生信息均调用该模块实现

#include <stdio.h>
#include <string.h>
#define N 2 // 运行程序输入测试时，可以把N改小一些输入测试

typedef struct student
{
	int id;			  // 学号
	char name[20];	  // 姓名
	char subject[20]; // 考试科目
	double perf;	  // 平时成绩
	double mid;		  // 期中成绩
	double final;	  // 期末成绩
	double total;	  // 总评成绩
	char level[10];	  // 成绩等级
} STU;

void input(STU[], int);		 // 录入学生信息
void output(STU[], int);	 // 输出学生信息
void calc(STU[], int);		 // 计算总评和等级
int fail(STU[], STU[], int); // 统计不及格学生信息
void sort(STU[], int);		 // 排序

int main()
{
	STU st[N], fst[N]; // 数组st记录学生信息，fst记录不及格学生信息
	int k;			   // 用于记录不及格学生个数

	printf("录入学生成绩信息:\n");
	input(st, N);

	printf("\n成绩处理...\n");
	calc(st, N);

	k = fail(st, fst, N);
	sort(st, N);
	printf("\n学生成绩排名情况:\n");
	output(st, N);

	printf("\n不及格学生信息:\n");
	output(fst, k);

	return 0;
}

void input(STU s[], int n)
{
	int i;

	for (i = 0; i < n; i++)
		scanf("%d %s %s %lf %lf %lf", &s[i].id, s[i].name, s[i].subject,
			  &s[i].perf, &s[i].mid, &s[i].final);
}

void output(STU s[], int n)
{
	int i;

	printf("-----------------\n");
	printf("学号   姓名     科目   平时   期中   期末   总评   等级\n");
	for (i = 0; i < n; i++)
		printf("%d   %-6s   %-4s   %-4.0f   %-4.0f   %-4.0f   %-4.1f   %s\n", s[i].id, s[i].name, s[i].subject, s[i].perf, s[i].mid, s[i].final, s[i].total, s[i].level);
}

void calc(STU s[], int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		s[i].total = s[i].perf * 0.2 +
					 s[i].mid * 0.2 +
					 s[i].final * 0.6;

		if (s[i].total >= 90)
			strcpy(s[i].level, "优");
		else if (s[i].total >= 80)
			strcpy(s[i].level, "良");
		else if (s[i].total >= 70)
			strcpy(s[i].level, "中");
		else if (s[i].total >= 60)
			strcpy(s[i].level, "及格");
		else
			strcpy(s[i].level, "不及格");
	}
}

int fail(STU s[], STU t[], int n)
{
	int i, cnt = 0;

	for (i = 0; i < n; i++)
		if (s[i].total < 60)
			t[cnt++] = s[i];

	return cnt;
}

void sort(STU s[], int n)
{
	int i, j;
	STU t;

	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - 1 - i; j++)
			if (s[j].total < s[j + 1].total)
			{
				t = s[j];
				s[j] = s[j + 1];
				s[j + 1] = t;
			}
}