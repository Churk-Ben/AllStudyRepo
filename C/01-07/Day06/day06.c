#include <stdio.h>

int main()
{
    char ans;
    while (1)
    {
        printf("Enter Your Answer:");
        scanf("%c", &ans);
        getchar();
        if (ans == 'a' || ans == 'A')
        {
            printf("Oooops!Try again\n");
            continue;
        }
        else if (ans == 'b' || ans == 'B')
        {
            printf("Oooops!Try again\n");
            continue;
        }
        else if (ans == 'c' || ans == 'C')
        {
            printf("Bingo~u r right!\n");
            break;
        }
        else
        {
            printf("Invalid input!\n");
            continue;
        }
    }
}