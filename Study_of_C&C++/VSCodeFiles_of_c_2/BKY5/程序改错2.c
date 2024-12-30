#include<stdio.h>
#define N 100
#define M 50
void fun(int *x,int *y,int *z,int n,int m,int *k)
{
	int i,j;

/**********ERROR**********/
	*k=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)

/**********ERROR**********/
			if(*(x+i)==*(y+j)) 
			{
				*(z+(*k)++)=*(x+i);

/**********ERROR**********/
				break;
			}
	}
}
int main()
{
	int a[N],b[M],i,j,k,n,m;
	int c[M]; 
	printf("输入n和m：");
	scanf("%d%d",&n,&m);
	printf("输入%d个整数：",n);
	for(i=0;i<n;i++)   
		scanf("%d",&a[i]);
	printf("输入%d个整数：",m);
	for(i=0;i<m;i++)
		scanf("%d",&b[i]);

/**********ERROR**********/
	fun(a,b,c,n,m,&k);
	printf("\n");
	for(i=0;i<k;i++)
		printf("%d ",c[i]);
	printf("\n");
	return 0;
}