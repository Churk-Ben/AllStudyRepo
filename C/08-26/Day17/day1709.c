#include <stdio.h>
#define MAX_SIZE 100

int main()
{
    int N;
    scanf("%d", &N);
    if (N <= 0 || N > MAX_SIZE)
    {
        return 1;
    }
    int arr[MAX_SIZE];
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }
    int cnt = 0;
    int found[MAX_SIZE] = {0};
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i != j && arr[i] == -arr[j] && !found[j])
            {
                cnt++;
                found[j] = 1;
                break;
            }
        }
    }
    cnt /= 2;
    printf("%d\n", cnt);
    return 0;
}
