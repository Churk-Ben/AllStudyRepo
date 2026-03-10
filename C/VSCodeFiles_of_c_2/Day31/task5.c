#include <stdio.h>
#define N 80

char *str_trunc(char *str, char x);

int main()
{
    char str[N];
    char ch;

    while (printf("输入字符串: "), gets(str) != NULL)
    {
        printf("输入一个字符: ");
        ch = getchar();

        printf("截断处理...\n");
        str_trunc(str, ch); // 函数调用

        printf("截断处理后的字符串: %s\n\n", str);
        getchar();
    }

    return 0;
}

// 函数str_trunc定义
// 功能: 对字符串作截断处理，把指定字符自第一次出现及其后的字符全部删除, 并返回字符串地址

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
