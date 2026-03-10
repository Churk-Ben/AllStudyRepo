#include<stdio.h>
#define N 100

/**********ERROR**********/
void fun(int *x,int n)
{
	int i,j,t;
	for(i=0;i<n-1;i++)

/**********ERROR**********/
		for(j=0;j<n-1;j++)
			if(*(x+j)<*(x+j+1))
			{

/**********ERROR**********/
				t=*(x+j);
				*(x+j)=*(x+j+1);

/**********ERROR**********/
				*(x+j+1)=t;
			}
}
int main()
{
	int i,n,a[N];
	printf("输入整数个数n: ");
	scanf("%d",&n);
	printf("输入%d个整数: ",n);
	for(i=0;i<n;i++)
		scanf("%d",a+i);
	fun(a,n);
	printf("\n排序后: ");
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}
