#include<stdio.h>
#define N 100
#define M 100

 /**********Begin**********/
 int fun(int *a, int *b, int *c, int n, int m)
 {
	 int *p, *q;
	 int cnt = 0;
	 for (p = a; p < a + n; p++)
	 {
		 for (q = b; q < b + m; q++)
		 {
			 if (*p == *q)
			 {
				 *(c + cnt) = *p;
				 cnt++;
			 }
		 }
	 }
	 return cnt;
 }

 /***********End***********/

int main()
{  
	FILE *in,*out;
	int a[N],b[M],c[N],i,k,n,m;
	printf("输入n和m: ");
	scanf("%d%d",&n,&m);
	printf("输入%d个整数: ",n);
	for(i=0;i<n;i++)   
		scanf("%d",&a[i]);
	printf("输入%d个整数: ",m);
	for(i=0;i<m;i++)
		scanf("%d",&b[i]);
	k=fun(a,b,c,n,m);
	printf("\n");
	for(i=0;i<k;i++)
		printf("%d ",c[i]);
	printf("\n");
	in=fopen("5.5.1.4_2-1.in","r");
	out=fopen("5.5.1.4_2-1.out","w");    
	while(fscanf(in,"%d%d",&n,&m)!=EOF)
	{
		for(i=0;i<n;i++)
			fscanf(in,"%d",&a[i]);
		for(i=0;i<m;i++)
			fscanf(in,"%d",&b[i]);
		k=fun(a,b,c,n,m);
		for(i=0;i<k;i++)
			fprintf(out,"%d ",c[i]);
		fprintf(out,"\n\n");
	}
	fclose(in);
	fclose(out);
	return 0;
}