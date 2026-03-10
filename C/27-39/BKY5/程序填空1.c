#include<stdio.h>
#define M 100
#define N 100
void merge(int *a,int *b,int *c,int m,int n)
{ 

/**********FILL**********/
	int i=0,j=0; 
	int k=0;

/**********FILL**********/
	while(i<m&&j<n)
	{
		if(*(a+i)<*(b+j))
		{
			*(c+k)=*(b+j);
 			j++; k++;
		}
		else
		{
			*(c+k)=*(a+i);
			i++; k++;
		}
	}
	while(i<m) 
	{

/**********FILL**********/
		*(c+k)=*(a+i);
		i++; k++;
	}
	while(j<n)
	{
 
/**********FILL**********/
		*(c+k)=*(b+j);
 		j++; k++;
	}
}
int main()
{
	int a[M],b[N],c[M+N];
	int m,n,i;
	scanf("%d",&m);
	for(i=0;i<m;i++)
		scanf("%d",&a[i]);
	scanf("%d",&n);
	for(i=0;i<n;i++)
		scanf("%d",&b[i]);	

/**********FILL**********/
	merge(a,b,c,m,n);
	printf("\n合并后: ");
	for(i=0;i<m+n;i++)
		printf("%3d",c[i]);
	printf("\n");
	return 0;
}