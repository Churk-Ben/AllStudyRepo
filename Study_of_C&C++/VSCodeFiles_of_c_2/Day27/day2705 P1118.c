#include <stdio.h>
#include <string.h>

int main()
{
    char a[14], mod[12] = "0123456789X";
    int n;
    scanf("%d", &n);
    getchar();

    while (n--)
    {
        fgets(a, sizeof(a), stdin);
        a[strcspn(a, "\n")] = '\0';

        int i, j = 1, t = 0;
        for (i = 0; i < 12; i++)
        {
            if (a[i] == '-')
            {
                continue;
            }
            t += (a[i] - '0') * j++;
        }
        if (mod[t % 11] == a[12])
        {
            printf("Right\n");
        }
        else
        {
            a[12] = mod[t % 11];
            puts(a);
        }
        getchar();
    }

    return 0;
}
