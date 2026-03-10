#include <stdio.h>

int main() {
    char in;
    while (scanf("%c", &in)!=EOF)
    {
        if (in=='r')
        {
            getchar();
            printf("stop!\n");
        }
        else if (in=='g')
        {
            getchar();
            printf("go go go\n");
        }
        else if (in=='y')
        {
            getchar();
            printf("wait a minute\n");
        }
        else
        {
            getchar();
            printf("something must be wrong\n");
        }
    }
}