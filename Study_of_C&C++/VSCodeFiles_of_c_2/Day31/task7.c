#include <stdio.h>
#define N 80
void encoder(char *str, int n); // 函数声明
void decoder(char *str, int n); // 函数声明

int main()
{
    char words[N];
    int n;

    printf("输入英文文本: ");
    gets(words);

    printf("输入n: ");
    scanf("%d", &n);

    printf("编码后的英文文本: ");
    encoder(words, n); // 函数调用
    printf("%s\n", words);

    printf("对编码后的英文文本解码: ");
    decoder(words, n); // 函数调用
    printf("%s\n", words);

    return 0;
}

/*函数定义
功能：对s指向的字符串进行编码处理
编码规则：
对于a~z或A~Z之间的字母字符，用其后第n个字符替换; 其它非字母字符，保持不变
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

/*函数定义
功能：对s指向的字符串进行解码处理
解码规则：
对于a~z或A~Z之间的字母字符，用其前面第n个字符替换; 其它非字母字符，保持不变
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