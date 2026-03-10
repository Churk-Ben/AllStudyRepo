#include <stdio.h>
#include <string.h>

int main() {
    char s1[100],s2[100];
    fgets(s1, 100, stdin);
    for (int i = 0; i < (int)strlen(s1); i++)
    {
        if (s1[i]>='A'&&s1[i]<='Z')
        {
            s2[i]=s1[i]+32;
        }
        else
        {
            s2[i]=s1[i];
        }
    }
    printf("%s", s2);
    return 0;
}