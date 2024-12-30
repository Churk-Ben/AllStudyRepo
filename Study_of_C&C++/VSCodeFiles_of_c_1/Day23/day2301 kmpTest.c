#include <stdio.h>
#include <string.h>

void computeLPSArray(char* patternstr, int patternlen, int* lps) {
    int length = 0; // 长度
    lps[0] = 0;     // 第一个字符的 lps 为 0
    int i = 1;

    while (i < patternlen) {
        if (patternstr[i] == patternstr[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1]; // 回退到上一个最长前缀
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(char* mainstr, char* patternstr) {
    int mainlen = strlen(mainstr);
    int patternlen = strlen(patternstr);
    int lps[patternlen];

    // 计算部分匹配表
    computeLPSArray(patternstr, patternlen, lps);

    int i = 0; // mainstr的索引
    int j = 0; // patternstr的索引
    int index[100], k = 0; // 记录匹配的位置

    while (i < mainlen) {
        if (patternstr[j] == mainstr[i]) {
            i++;
            j++;
        }

        if (j == patternlen) {
            index[k] = i - j; // 找到匹配的位置
            k++;
            j = lps[j - 1]; // 继续寻找下一个匹配
        } else if (i < mainlen && patternstr[j] != mainstr[i]) {
            // mismatch after j matches
            if (j != 0) {
                j = lps[j - 1]; // 使用 lps 表回退模式字符串
            } else {
                i++;
            }
        }
    }

    printf("Index of pattern in main string are: ");
    for (int m = 0; m < k; m++) {
        printf("%d ", index[m]);
    }
}

int main() {
    char mainstr[100], patternstr[100];
    fgets(mainstr, sizeof(mainstr), stdin);
    fgets(patternstr, sizeof(patternstr), stdin);
    
    // 去掉输入字符串的换行符
    mainstr[strcspn(mainstr, "\n")] = 0;
    patternstr[strcspn(patternstr, "\n")] = 0;

    KMPSearch(mainstr, patternstr);

    return 0;
}

