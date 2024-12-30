#include<stdio.h>
#define N 100
void fun(int m,int k,int x[])
{

/**********FILL**********/
	int n=0;
	int i,j; 

/**********FILL**********/
	for(i=m+1;n<k;i++)
	{
		for(j=2;j<i;j++) 

/**********FILL**********/
			if(i%j==0)
				break; 

/**********FILL**********/
		if(j==i)
			x[n++]=i; 
	}
}
int main()
{
	int m,k,i,a[N];
	scanf("%d%d",&m,&k);

/**********FILL**********/
	fun(m,k,a);
	for(i=0;i<k;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}