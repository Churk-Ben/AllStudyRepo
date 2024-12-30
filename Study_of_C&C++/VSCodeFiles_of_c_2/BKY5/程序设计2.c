#include<stdio.h>
#define N 100
#define M 10

/***********Begin*********/
double fun(int a[][M],int b[N],int n,int m,int *k)
{
	int sum[N];
	double avg=0;
	int i,j;
	*k=0;
	for(i=0;i<n;i++)
	{
		sum[i]=0;
		for(j=0;j<m;j++)
		{
			sum[i]+=a[i][j];
		}
	}
	for(i=0;i<n;i++)
	{
		avg+=sum[i];
	}
	avg=avg/n;
	for(i=0;i<n;i++)
	{
		if(sum[i]<avg)
		{
			b[*k]=sum[i];
			(*k)++;
		}
	}
	return avg;
}


/***********End***********/

int main()
{
	FILE *in,*out;
	int a[N][M],b[N],i,j,n,m,k;
	double avg;
	printf("输入学生人数n和课程数m: ");
	scanf("%d%d",&n,&m);
	printf("依次输入每名学生的成绩:\n");
	for(i=0;i<n;i++)
		for(j=0;j<m;j++) 
			scanf("%d",&a[i][j]);
	avg=fun(a,b,n,m,&k);
	printf("\n班级总平均分: %.2lf\n",avg);
	printf("总分低于平均分的人数: %d\n",k);
	for(i=0;i<k;i++)
		printf("%4d",b[i]);
	printf("\n");
	in=fopen("6.5.2.6_1_3.in","r");
	out=fopen("6.5.2.6_1_3.out","w");    
	while(fscanf(in,"%d%d",&n,&m)!=EOF)
	{
		for(i=0;i<n;i++)
			for(j=0;j<m;j++)
				fscanf(in,"%d",&a[i][j]);
		avg=fun(a,b,n,m,&k);
		fprintf(out,"班级总平均分: %.2lf\n",avg);
		fprintf(out,"总分低于平均分的人数: %d\n",k);
		for(i=0;i<k;i++)
			fprintf(out,"%4d",b[i]);
		fprintf(out,"\n\n");
	}
	fclose(in);
	fclose(out);
	return 0;
}