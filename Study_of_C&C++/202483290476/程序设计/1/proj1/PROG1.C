/*
请编写函数fun，其功能是：求一个二维数组中每一行的最小元素的平均值，结果作为函数值返回。
程序运行时，若依次输入：
3 4
10 6 3 4
6 7 8 12
9 12 6 2
则输出结果为：
每行最小元素的平均值: 3.6666666667
注意：部分源程序已给出，请勿改动main函数和其他已有的任何内容，仅在注释"Begin"和"End"之间填入所编写的若干语句。 
试题程序：
*/
#include<stdio.h>
#define M 100
#define N 50

 /*********Begin********/
double fun(int a[][N],int m,int n){
	double avg = 0;
	int i,j;
	int min;
	for(i=1;i<=m;i++){
		min=a[i][1];
		for(j=2;j<=n;j++){
			if(a[i][j]<min){
				min=a[i][j];
			}
		}
		avg+=min;
	}
	avg/=m;
	return avg;
}


 /*********End**********/

int main()
{
	FILE *in,*out;
	int a[M][N],m,n,i,j;
	printf("输入数组行数m和列数n: ");
	scanf("%d%d",&m,&n);
	printf("按行输入数组元素:\n");
	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	printf("\n每行最小元素的平均值: %.10lf\n",fun(a,m,n));
	in=fopen("5.5.2.1_5-3-2.in","r");
	out=fopen("5.5.2.1_5-3-2.out","w");
	while(fscanf(in,"%d%d",&m,&n)!=EOF)
	{
		for(i=1;i<=m;i++)
			for(j=1;j<=n;j++)
				fscanf(in,"%d",&a[i][j]);
		fprintf(out,"%.10lf\n",fun(a,m,n));
	}
	fclose(in);
	fclose(out);
	return 0;
}