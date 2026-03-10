#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 500
#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

void find_longest_and_shortest_word(const char *str, char *longest, char *shortest) {
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int word_count = 0;

    // 拆分字符串为单词
    const char *token = strtok(str, " ");
    while (token != NULL) {
        strcpy(words[word_count++], token);
        token = strtok(NULL, " ");
    }

    // 初始化最长和最短单词
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

    printf("请输入字符串（长度小于500）：\n");
    fgets(str, MAX_LENGTH, stdin);

    // 去掉末尾换行符
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    // 找出最长和最短的单词
    find_longest_and_shortest_word(str, longest, shortest);

    printf("最长单词是: %s\n", longest);
    printf("最短单词是: %s\n", shortest);

    return 0;
}
