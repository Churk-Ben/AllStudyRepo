#include <stdio.h>
#define N 80
void encoder(char *str, int n); // ��������
void decoder(char *str, int n); // ��������

int main()
{
    char words[N];
    int n;

    printf("����Ӣ���ı�: ");
    gets(words);

    printf("����n: ");
    scanf("%d", &n);

    printf("������Ӣ���ı�: ");
    encoder(words, n); // ��������
    printf("%s\n", words);

    printf("�Ա�����Ӣ���ı�����: ");
    decoder(words, n); // ��������
    printf("%s\n", words);

    return 0;
}

/*��������
���ܣ���sָ����ַ������б��봦��
�������
����a~z��A~Z֮�����ĸ�ַ���������n���ַ��滻; ��������ĸ�ַ������ֲ���
*/
void encoder(char *str, int n)
{
    while (*str)
    {
        if (*str >= 'a' && *str <= 'z')
        {
            *str = (*str - 'a' + n + 26) % 26 + 'a';
        }
        if (*str >= 'A' && *str <= 'Z')
        {
            *str = (*str - 'A' + n + 26) % 26 + 'A';
        }
        str++;
    }
}

/*��������
���ܣ���sָ����ַ������н��봦��
�������
����a~z��A~Z֮�����ĸ�ַ�������ǰ���n���ַ��滻; ��������ĸ�ַ������ֲ���
*/
void decoder(char *str, int n)
{
    while (*str)
    {
        if (*str >= 'a' && *str <= 'z')
        {
            *str = (*str - 'a' - n + 26) % 26 + 'a';
        }
        if (*str >= 'A' && *str <= 'Z')
        {
            *str = (*str - 'A' - n + 26) % 26 + 'A';
        }
        str++;
    }
}