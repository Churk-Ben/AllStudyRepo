#include<stdio.h>
#define N 100
void fun(char s[])
{

/**********FILL**********/
	int k=0,i=0;
	char t; 
	while(s[k]!='\0')

/**********FILL**********/
		    k++;
	k-=1; 

/**********FILL**********/
	while(i<k)
	{
		t=s[i]; 

/**********FILL**********/
		s[i]=s[k];
		s[k]=t; 
		i++,k--; 
	}
}
int main()
{
	char a[N]; 
	printf("输入字符串: ");
	gets(a);

/**********FILL**********/
	fun(a);
	printf("\n首尾逆置后:\n");
	puts(a);
	return 0;	
}