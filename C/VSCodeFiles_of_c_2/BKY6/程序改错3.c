#include<stdio.h>
#include<string.h>
#define N 100
void fun(char *str)
{
	int i,len;
	char t;

/**********ERROR**********/
	len=strlen(str);
	t=*(str+len-1);
	for(i=len-1;i>0;i--)

/**********ERROR**********/
		*(str+i)=*(str+i-1);
	*str=t;
}
int main()
{
	int k;

/**********ERROR**********/
	char s[N];
	printf("输入字符串: ");
	gets(s); 
	printf("输入移动字符数k: ");
	scanf("%d",&k);
	while(k--)

/**********ERROR**********/
		fun(s); 
	printf("\n移动后字符串: %s\n",s);
	return 0;
}