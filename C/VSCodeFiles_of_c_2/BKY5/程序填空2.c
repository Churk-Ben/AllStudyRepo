#include<stdio.h>
#define N 100
void fun(int *x,int n,double *avg)
{
	int i,j,y[N];

/**********FILL**********/
	*avg=0;
	for(i=0;i<n;i++)
		*avg+=*(x+i); 

/**********FILL**********/
	    *avg=*avg/n;
	for(i=0,j=0;i<n;i++)
	{
		if(*(x+i)<*avg)  
		{

/**********FILL**********/
			y[j++]=*(x+i);
			*(x+i)=-1;
		}
	}
	i=0; 
	while(i<n) 
	{

/**********FILL**********/
		if(*(x+i)!=-1)
			*(y+j++)=*(x+i); 
		i++; 
	}
	for(i=0;i<n;i++)
		*(x+i)=*(y+i); 
}
int main()
{
	int a[N],n,i;
	double avg; 
	printf("请输入元素个数n: ");
	scanf("%d",&n);
	printf("请输入n个整数: ");
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);

/**********FILL**********/
	fun(a,n,&avg);
	printf("\n平均值: %.8lf\n",avg);
	printf("移动后: ");
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");  
	return 0;	
}