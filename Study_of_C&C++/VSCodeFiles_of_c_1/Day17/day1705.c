#include <stdio.h>

int main()
{
    int input;
    int s[1000];
    s[0] = 0;
    for (int i = 1; i <= 1000; i++)
    {
        s[i] = 0;
    }

    while (scanf("%d", &input) != EOF)
    {
        if (input==-1)
        {
            break;
        }
        
        s[input] += 1;
    }

    for (int i = 1; i <= 1000; i++)
    {
        if (s[i] > 0)
        {
            printf("%d %d\n", i, s[i]);
        }
    }
    return 0;
}
