#include<stdio.h>
#define M 100
#define N 100

/**********FILL**********/
double fun(int x[][N],int m,int n)
{
	int i,j, min;
	double avg=0;
	for(i=0;i<m;i++) 
	{

/**********FILL**********/
		min=x[i][0];
		for(j=1;j<n;j++) 
			if(min>x[i][j])

/**********FILL**********/
				    min=x[i][j];
		avg+=min;
	}

/**********FILL**********/
	return   avg/m;
}
int main()
{
	int a[M][N],m,n,i,j;
	double avg;    
	printf("输入矩阵行数m和列数n：");   
	scanf("%d%d",&m,&n);
	printf("按行输入矩阵a的元素：\n");
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)

/**********FILL**********/
			scanf("%d",&a[i][j]);
	avg=fun(a,m,n);
	printf("\n每行最小元素的平均值为: %.8lf\n",avg); 
	return 0;
}