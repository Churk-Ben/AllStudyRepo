#include<stdio.h>
#define M 100
#define N 100
void fun(char *str1,char *str2,char *t)
{
	for(;*str1&&*str2;t++)
	{

/**********ERROR**********/
		if(*str1>*str2)
			*t=*str1++; 
		else
			*t=*str2++;
	}

/**********ERROR**********/
	for(;*str1!='\0';t++,str1++)
		*t=*str1;

/**********ERROR**********/
	for(;*str2!='\0';t++,str2++)
		*t=*str2; 

/**********ERROR**********/
	*t='\0'; 
}
int main()
{
	char x[M],y[N], z[M+N];
	gets(x);
	gets(y);

/**********ERROR**********/
	fun(x,y,z);
	printf("\n合并后: %s\n",z); 
	return 0;
}