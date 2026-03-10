#include<stdio.h>
#define N 100

/**********ERROR**********/
int a[N][N]; 
void fun(int n)
{
	int i,j,t;
	for(i=0;i<n;i++)

/**********ERROR**********/
		for(j=0;j<i;j++)
		{

/**********ERROR**********/
			t=a[i][j]; 
			a[i][j]=a[j][i]; 

/**********ERROR**********/
			a[j][i]=t;
		}		
}
int main()
{
	int n,i,j; 
	printf("输入矩阵阶数n: "); 
	scanf("%d",&n);
	printf("按行输入矩阵元素:\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&a[i][j]);

/**********ERROR**********/
	fun(n); 
	printf("\n转置后:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			printf("%4d",a[i][j]);
		printf("\n");
	}
	printf("\n");
	return 0;
}