#include <stdio.h>
#include <string.h>

// 函数声明
void computeNext(const char *pattern, int *next);
void kmpSearch(const char *text, const char *pattern);

int main() {
    char text[100];
    char pattern[100];

    // 输入主串和模式串
    printf("请输入主串: ");
    fgets(text, sizeof(text), stdin);
    printf("请输入模式串: ");
    fgets(pattern, sizeof(pattern), stdin);

    // 去掉换行符
    text[strcspn(text, "\n")] = '\0';
    pattern[strcspn(pattern, "\n")] = '\0';

    // 调用 KMP 查找函数
    kmpSearch(text, pattern);

    return 0;
}

// 计算模式串的 next 数组
void computeNext(const char *pattern, int *next) {
    int m = strlen(pattern);
    next[0] = 0; // next[0] 是始终为 0

    int j = 0; // j 代表前缀长度
    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1]; // 回溯到前一个最佳匹配
        }
        if (pattern[i] == pattern[j]) {
            j++; // 匹配继续
        }
        next[i] = j; // 记录当前字符匹配的前缀长度
    }
}

// KMP 字符串查找
void kmpSearch(const char *text, const char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int next[m];

    // 计算模式串的 next 数组
    computeNext(pattern, next);

    int j = 0; // j 代表当前匹配的模式串中的位置
    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1]; // 发生不匹配，回溯到前一个最佳匹配
        }
        if (text[i] == pattern[j]) {
            j++; // 字符匹配，移动到模式串的下一个位置
        }
        if (j == m) {
            printf("找到匹配，起始位置: %d\n", i - m + 1); // 找到匹配，输出起始位置
            j = next[j - 1]; // 准备进行下一个匹配
        }
    }
}
