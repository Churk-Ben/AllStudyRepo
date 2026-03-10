#include <stdio.h>

int hanoi(int n, char from, char to, char via)
{
    if (n == 1)
    {
        printf("1 : %c -> %c\n", from, to);
        return 1;
    }

    int cnt = hanoi(n - 1, from, via, to) + 1;
    printf("%d : %c -> %c\n", n, from, to);
    cnt += hanoi(n - 1, via, to, from);

    return cnt;
}

int main()
{
    int n;
    char from, to, via;
    while (scanf("%d", &n) != EOF)
    {
        getchar();
        scanf("%c %c %c", &from, &via, &to);

        int cnt = hanoi(n, from, to, via);
        printf("Total moves: %d\n\n", cnt);
    }

    return 0;
}