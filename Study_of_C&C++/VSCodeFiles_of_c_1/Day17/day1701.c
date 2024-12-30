#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 500
#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

void find_longest_and_shortest_word(const char *str, char *longest, char *shortest) {
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int word_count = 0;

    // ����ַ���Ϊ����
    const char *token = strtok(str, " ");
    while (token != NULL) {
        strcpy(words[word_count++], token);
        token = strtok(NULL, " ");
    }

    // ��ʼ�������̵���
    strcpy(longest, words[0]);
    strcpy(shortest, words[0]);

    for (int i = 1; i < word_count; i++) {
        if (strlen(words[i]) > strlen(longest)) {
            strcpy(longest, words[i]);
        }
        if (strlen(words[i]) < strlen(shortest)) {
            strcpy(shortest, words[i]);
        }
    }
}

int main() {
    char str[MAX_LENGTH];
    char longest[MAX_WORD_LENGTH];
    char shortest[MAX_WORD_LENGTH];

    printf("�������ַ���������С��500����\n");
    fgets(str, MAX_LENGTH, stdin);

    // ȥ��ĩβ���з�
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    // �ҳ������̵ĵ���
    find_longest_and_shortest_word(str, longest, shortest);

    printf("�������: %s\n", longest);
    printf("��̵�����: %s\n", shortest);

    return 0;
}
