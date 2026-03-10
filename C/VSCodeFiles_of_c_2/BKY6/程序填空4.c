#include<stdio.h>
#define N 100
void fun(char *a)
{

/**********FILL**********/
	char *p=a; 
	while(*p=='*')

/**********FILL**********/
		     p++;
	while(*p)
	{

/**********FILL**********/
		*a=*p;
		a++,p++;  
	}

/**********FILL**********/
	     *a='\0';
}
int main()
{
	char a[N];
	printf("输入字符串: ");
	gets(a);

/**********FILL**********/
	    fun(a); 
	printf("\n处理后:\n");
	printf("%s\n",a);
	return 0;	
}