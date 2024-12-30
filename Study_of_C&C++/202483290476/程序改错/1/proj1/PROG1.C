/*
假设两个字符串str1和str2中的字符都是按照字符（ASCII码）从大到小的顺序排列的。
函数fun的功能是将它们合并为一个字符串，要求合并后的字符串中的字符仍然按原来的顺序排列。
程序运行时，若分别输入KIGECA8642和LJHFDB97531，合并后得到的字符串为：LKJIHGFEDCBA987654321。
请改正程序中指定部位的错误，使之能得到正确的结果。
注意：只允许修改注释"ERROR"的下一行，不得改动程序中的其他内容，也不允许增加或删减语句。
试题源程序：
*/
#include<stdio.h>
#define M 100
#define N 100
void fun(char *str1,char *str2,char *t)
{
	for(;*str1&&*str2;t++)
	{
		if(*str1>*str2)
			*t=*str1++;
		else
			*t=*str2++;
	}
	for(;*str1;t++,str1++)

/**********ERROR**********/
		*t=*str1;
	for(;*str2;t++,str2++)

/**********ERROR**********/
		*t=*str2;
	*t=0; 
}
int main()
{
	char x[M],y[N];
	char z[M+N];
	gets(x);
	gets(y);

/**********ERROR**********/
	fun(x,y,z);
	printf("\n合并后: %s\n",z); 
	return 0;
}