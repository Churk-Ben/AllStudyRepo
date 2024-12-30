//gjchengfa
#include <stdio.h>
#define N 201
int result[N] = {0};

// ���º������ڽ�һ���ַ������������
void reverse(char *s, int n);

// ���º������ڼ�¼һ���ַ����е��ַ������������������ַ�
int count_str(char *s);

int main()
{
    char num1[100], num2[100];
    int pin;
    while (scanf("%s", num1) != EOF)
    {

        getchar();
        scanf("%s", num2);
        getchar();

        int cnum1 = count_str(num1);
        int cnum2 = count_str(num2);

        reverse(num1, cnum1);
        reverse(num2, cnum2);
        int len;
        for (int i = 0; i < cnum1; i++)
        {
            pin = 0;
            for (int j = 0; j < cnum2; j++)
            {
                int temp = result[i + j] + (int)(num1[i] - '0') * (int)(num2[j] - '0') + pin; // ����ע��Ҫ���ַ������е��ַ��͵�����ת�������Ӧ������
                result[i + j] = temp % 10;
                pin = temp / 10;
                len = i + j; // ���������Ŀ���Ǽ�¼���½�������е����ֵĸ��������������������
            }
            if (pin)
            {
                result[cnum2 + i] = pin;
                len = cnum2 + i;
            }
        }
        for (int k = len; k >= 0; k--)
        {
            printf("%d", result[k]);
        }
        printf("\n");
    }
}

void reverse(char *s, int n)
{
    int i, j;
    char temp;
    for (i = 0, j = n - 1; i < j; i++, j--)
    {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
    return;
}

int count_str(char *s)
{
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        count++;
    }
    return count;
}