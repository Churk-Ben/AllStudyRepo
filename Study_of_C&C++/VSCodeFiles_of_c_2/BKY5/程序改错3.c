#include<stdio.h>
#define N 100
void fun(char *str)
{
	char *p,*q,t;
	p=q=str; 

/**********ERROR**********/
	while(*q!='\0')
		q++; 

/**********ERROR**********/
	q--;
	while(p<q) 
	{
		t=*p; 

/**********ERROR**********/
		*p=*q; 
		*q=t;

/**********ERROR**********/
		p++;
		q--; 
	}	
}
int main()
{
	char s[N]; 
	printf("输入字符串: ");
	gets(s);

/**********ERROR**********/
	fun(s); 
	printf("\n首尾逆置后: ");
	puts(s);
	return 0;	
}