#include <stdio.h>
#define N 80

char *str_trunc(char *str, char x);

int main()
{
    char str[N];
    char ch;

    while (printf("�����ַ���: "), gets(str) != NULL)
    {
        printf("����һ���ַ�: ");
        ch = getchar();

        printf("�ضϴ���...\n");
        str_trunc(str, ch); // ��������

        printf("�ضϴ������ַ���: %s\n\n", str);
        getchar();
    }

    return 0;
}

// ����str_trunc����
// ����: ���ַ������ضϴ�����ָ���ַ��Ե�һ�γ��ּ������ַ�ȫ��ɾ��, �������ַ�����ַ

char *str_trunc(char *str, char ch)
{
    char *ptr = str;
    while (*ptr)
    {
        if (*ptr == ch)
        {                
            *ptr = '\0';
            break;
        }
        ptr++;
    }
    return str;
}
