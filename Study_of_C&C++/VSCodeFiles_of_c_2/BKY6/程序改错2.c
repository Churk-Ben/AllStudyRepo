#include<stdio.h>
#define M 100
#define N 100
void fun(int x[][N],int y[][M],int m,int n)
{
	int i,j; 

/**********ERROR**********/
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++)
			y[i][j]=x[m+1-j][i]; 
}
int main()
{
	int a[M][N],b[N][M];
	int m,n,i,j;
	printf("输入原矩阵行数m和列数n: "); 

/**********ERROR**********/
	scanf("%d%d",&m,&n);
	printf("按行输入矩阵元素:\n");
	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++)
			scanf("%d",&a[i][j]);

/**********ERROR**********/
	fun(a,b,m,n);
	printf("\n旋转后:\n");
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
			printf("%3d",b[i][j]);
		printf("\n");
	}
	printf("\n");
	return 0;
}