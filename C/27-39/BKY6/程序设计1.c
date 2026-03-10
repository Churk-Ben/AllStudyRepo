#include<stdio.h>

/*********Begin********/
double fun(int n,double x)
{
	int i;
	double pre1=1,pre2=2,sign=1;
	double s=3/2.0,a=x;
	for(i=0;i<n-2;i++)
	{
		s=s+a/(pre1+pre2)*sign*1.0;
		pre2=pre1+pre2;
		pre1=pre2-pre1;
		a*=x;
		sign=-sign;
	}
	return s;
}


/*********End**********/

int main()
{
	FILE *in,*out;
	int n;
	double x;
	printf("依次输入n和x: ");
	scanf("%d%lf",&n,&x);
	printf("\ns=%.10lf\n",fun(n,x));
	in=fopen("4.5.1.5_1_8.in","r");
	out=fopen("4.5.1.5_1_8.out","w");
	while(fscanf(in,"%d%lf",&n,&x)!=EOF)
		fprintf(out,"%.10lf\n",fun(n,x));
	fclose(out);
	fclose(in);
	return 0;
}