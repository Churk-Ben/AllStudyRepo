#include <stdio.h>
#define N 80

void replace(char *str, char old_char, char new_char); // ��������

int main() {
    char text[N] = "Programming is difficult or not, it is a question.";

    printf("ԭʼ�ı�: \n");
    printf("%s\n", text);

    replace(text, 'i', '*'); // �������� ע���ַ��β�д���������Ų�����

    printf("������ı�: \n");
    printf("%s\n", text);

    return 0;
}

// ��������
void replace(char *str, char old_char, char new_char) {
    int i;

    while(*str) {
        if(*str == old_char)
            *str = new_char;
        str++;
    }
}