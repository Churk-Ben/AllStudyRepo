/*
某校计算机专业《程序设计基础》课程的期末总评成绩按平时表现10%、课程作业20%、课程实验10%、期末考试60%计算。
学生信息包括：学号、姓名、平时成绩、作业成绩、实验成绩、期末考试成绩、总评成绩和成绩等级。
fun函数的功能是：计算课程总评成绩，将总评成绩大于等于90的学生成绩等级设置为"优秀"、大于等于80而小于90的学生成绩等级设置为"良好"、大于等于70而小于80的学生成绩等级设置为"中等"、大于等于60而小于70的学生成绩等级设置为"及格"、小于60的学生成绩等级设置为"不及格"。同时将等级为"优秀"或"良好"的学生信息保存在数组h中，优秀或良好等级的学生人数由形参m获得。
主函数中输入n名学生的学号、姓名以及各单项成绩（百分制），调用fun函数，并输出所有优秀或良好等级的学生信息。
程序运行时，若依次输入：
6
101 B1 100 100 100 84
102 B2 100 100 100 34
103 G1 95 95 90 95
104 B3 80 58 52 80
105 G2 85 80 85 80
106 B4 10 10 10 91
则输出结果为：
优良等级人数: 3
 101  B1 90.4  优秀
 103  G1 94.5  优秀
 105  G2 81.0  良好
注意：部分源程序已给出，请勿改动main函数和其他已有的任何内容，仅在注释"Begin"和"End"之间填入所编写的若干语句。 
试题程序：
*/
#include<stdio.h>
#include<string.h>
#define N 100
typedef struct
{
	int num; /*学号*/
	char name[16]; /*姓名*/
	int s1; /*平时成绩*/
	int s2; /*作业成绩*/
	int s3; /*实验成绩*/
	int s4; /*期末考试成绩*/
	double score; /*总评成绩*/
	char level[8]; /*成绩等级*/
}STUREC;

/***********Begin*********/
void fun(STUREC s[],STUREC h[], int n, int *k){
	int i;
	int cnt = 0;

	for(i=0;i<n;i++){
		s[i].score = s[i].s1*0.1+s[i].s2*0.2+s[i].s3*0.1+s[i].s4*0.6;

		if(s[i].score>=90){
			strcpy(s[i].level,"优秀");
			h[cnt++]=s[i];
		}
		else if(s[i].score>=80){
			strcpy(s[i].level,"良好");
			h[cnt++]=s[i];
		}
		else if(s[i].score>=70)
			strcpy(s[i].level,"中等");
		else if(s[i].score>=60)
			strcpy(s[i].level,"及格");
		else
			strcpy(s[i].level,"不及格");
	}
	*k = cnt;
}
	
/***********End***********/

int main()
{
	FILE *in,*out;
	STUREC s[N],h[N];
	int i,n,k;
	scanf("%d",&n);
	for(i=0;i<n;i++)
		scanf("%d%s%d%d%d%d",&s[i].num,s[i].name,&s[i].s1,&s[i].s2,&s[i].s3,&s[i].s4);
	fun(s,h,n,&k);
	printf("\n优良等级人数: %d\n",k);
	for(i=0;i<k;i++)
		printf("%4d%4s%5.1lf%6s\n",h[i].num,h[i].name,h[i].score,h[i].level);
	in=fopen("8.5.1.2_1-2-6-2.in","r");
	out=fopen("8.5.1.2_1-2-6-2.out","w");    
	while(fscanf(in,"%d",&n)!=EOF)
	{
		for(i=0;i<n;i++)
			fscanf(in,"%d%s%d%d%d%d",&s[i].num,s[i].name,&s[i].s1,&s[i].s2,&s[i].s3,&s[i].s4);
		fun(s,h,n,&k);
		for(i=0;i<n;i++)
			fprintf(out,"%4d%8s%6.1lf%8s\n",s[i].num,s[i].name,s[i].score,s[i].level);
		fprintf(out,"优良等级人数: %d\n",k);
		for(i=0;i<k;i++)
			fprintf(out,"%4d%8s%6.1lf%6s\n",h[i].num,h[i].name,h[i].score,h[i].level);
		fprintf(out,"\n");
	}
	fclose(in);
	fclose(out);
	return 0;
}