#include<stdio.h>
#include<string.h>
void fun(char *ps[], int n)
{

/**********FILL**********/
	char *temp;
	int i,j,k;

/**********FILL**********/
	for(i=0;i<n-1;i++)
	{
		k=i; 
		for(j=i+1;j<n-1;j++)

/**********FILL**********/
			if(strcmp(ps[j],ps[k])>0)
				k=j;

/**********FILL**********/
		if(k!=i)
		{
			temp=ps[i]; 
			ps[i]=ps[k];
			ps[k]=temp; 
		}
	}
} 
int main()
{
	char *ps[5]={ "C Programming", "C++ Object-Oriented Programming", "Python Programming", "Operating System", "Data Structure and Algorithms" };
	int i;

/**********FILL**********/
	fun(ps,5);
	for(i=0;i<5;i++)
		printf("%s\n",ps[i]);
	return 0;
}