#include<stdio.h>
#define N 100

/***********Begin*********/
void fun (int *score,int *h,int n,int *k)
{
	double avg=0;
	int i;
	*k=0;
	for(i=0;i<n;i++)
	{
		avg+=*(score+i);
	}
	avg=avg/n;
	for(i=0;i<n;i++)
	{
		if(*(score+i)<avg)
		{
			*(h+*k)=*(score+i);
			(*k)++;
		}
	}
}
/***********End***********/

int main()
{
	FILE *in,*out;
	int score[N],h[N];
	int i,n,k;
	printf("输入学生数量n: ");
	scanf("%d",&n);
	printf("输入%d名学生的成绩: ",n);
	for(i=0;i<n;i++)
		scanf("%d",&score[i]);
	fun(score,h,n,&k);
	printf("\n低于平均分的人数: %d\n",k);
	printf("具体成绩: ");
	for(i=0;i<k;i++)
		printf("%3d",h[i]);
	printf("\n");
	in=fopen("6.5.1.6_1_1.in","r");
	out=fopen("6.5.1.6_1_1.out","w");    
	while(fscanf(in,"%d",&n)!=EOF)
	{
		for(i=0;i<n;i++)
			fscanf(in,"%d",&score[i]);
		fun(score,h,n,&k);
		fprintf(out,"%d\n",k);
		for(i=0;i<k;i++)
			fprintf(out,"%4d",h[i]);
		fprintf(out,"\n");
	}
	fclose(in);
	fclose(out);
	return 0;
}