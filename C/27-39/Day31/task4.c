#include <stdio.h>
#define N 80

void replace(char *str, char old_char, char new_char); // 函数声明

int main() {
    char text[N] = "Programming is difficult or not, it is a question.";

    printf("原始文本: \n");
    printf("%s\n", text);

    replace(text, 'i', '*'); // 函数调用 注意字符形参写法，单引号不能少

    printf("处理后文本: \n");
    printf("%s\n", text);

    return 0;
}

// 函数定义
void replace(char *str, char old_char, char new_char) {
    int i;

    while(*str) {
        if(*str == old_char)
            *str = new_char;
        str++;
    }
}