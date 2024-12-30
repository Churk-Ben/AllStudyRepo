#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int hats[100];
    for (int i = 0; i < n; i++)
        scanf("%d", &hats[i]);

    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; i++)
    {
        int guesses[100];
        int ycnt = 0, ncnt = 0, hcnt = 0;

        for (int j = 0; j < n; j++)
        {
            scanf("%d", &guesses[j]);
            if (guesses[j] != 0)
            {                 
                hcnt = 1;
                if (guesses[j] == hats[j])
                {
                    ycnt++;
                }
                else
                {
                    ncnt++;
                }
            }
        }

        if (ncnt == 0 && ycnt > 0 && hcnt)
        {
            printf("Da Jiang!!!\n");
        }
        else
        {
            printf("Ai Ya\n");
        }
    }

    return 0;
}
