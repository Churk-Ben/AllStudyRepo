#include <stdio.h>
#include <string.h>
#define N 80

int main() {
    char s1[N] = "Learning makes me happy";
    char s2[N] = "Learning makes me sleepy";
    char tmp[N];

    printf("sizeof(s1) vs. strlen(s1): \n");
    printf("sizeof(s1) = %d\n", sizeof(s1));
    printf("strlen(s1) = %d\n", strlen(s1));

    printf("\nbefore swap: \n");
    printf("s1: %s\n", s1);
    printf("s2: %s\n", s2);

    printf("\nswapping...\n");
    strcpy(tmp, s1);
    strcpy(s1, s2);
    strcpy(s2, tmp);

    printf("\nafter swap: \n");
    printf("s1: %s\n", s1);
    printf("s2: %s\n", s2);

    return 0;
}