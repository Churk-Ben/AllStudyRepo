#include <stdio.h>
#include <string.h>

// ��������
void computeNext(const char *pattern, int *next);
void kmpSearch(const char *text, const char *pattern);

int main() {
    char text[100];
    char pattern[100];

    // ����������ģʽ��
    printf("����������: ");
    fgets(text, sizeof(text), stdin);
    printf("������ģʽ��: ");
    fgets(pattern, sizeof(pattern), stdin);

    // ȥ�����з�
    text[strcspn(text, "\n")] = '\0';
    pattern[strcspn(pattern, "\n")] = '\0';

    // ���� KMP ���Һ���
    kmpSearch(text, pattern);

    return 0;
}

// ����ģʽ���� next ����
void computeNext(const char *pattern, int *next) {
    int m = strlen(pattern);
    next[0] = 0; // next[0] ��ʼ��Ϊ 0

    int j = 0; // j ����ǰ׺����
    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1]; // ���ݵ�ǰһ�����ƥ��
        }
        if (pattern[i] == pattern[j]) {
            j++; // ƥ�����
        }
        next[i] = j; // ��¼��ǰ�ַ�ƥ���ǰ׺����
    }
}

// KMP �ַ�������
void kmpSearch(const char *text, const char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int next[m];

    // ����ģʽ���� next ����
    computeNext(pattern, next);

    int j = 0; // j ����ǰƥ���ģʽ���е�λ��
    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1]; // ������ƥ�䣬���ݵ�ǰһ�����ƥ��
        }
        if (text[i] == pattern[j]) {
            j++; // �ַ�ƥ�䣬�ƶ���ģʽ������һ��λ��
        }
        if (j == m) {
            printf("�ҵ�ƥ�䣬��ʼλ��: %d\n", i - m + 1); // �ҵ�ƥ�䣬�����ʼλ��
            j = next[j - 1]; // ׼��������һ��ƥ��
        }
    }
}
