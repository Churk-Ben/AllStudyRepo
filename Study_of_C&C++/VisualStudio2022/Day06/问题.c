#include <stdio.h>
int main()
{
    int n;
    int s = 0, m = 1;
    while (scanf("%d", &n) != EOF)
    {
        if (n > 0)
        {
            for (int i = 0; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    m *= j;
                }
                s += m;
                m = 1;
            }
        }

        printf("%d\n", s);
    }
    return 0;
}