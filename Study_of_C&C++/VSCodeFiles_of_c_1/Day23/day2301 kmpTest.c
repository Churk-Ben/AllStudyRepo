#include <stdio.h>
#include <string.h>

void computeLPSArray(char* patternstr, int patternlen, int* lps) {
    int length = 0; // ����
    lps[0] = 0;     // ��һ���ַ��� lps Ϊ 0
    int i = 1;

    while (i < patternlen) {
        if (patternstr[i] == patternstr[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1]; // ���˵���һ���ǰ׺
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

    // ���㲿��ƥ���
    computeLPSArray(patternstr, patternlen, lps);

    int i = 0; // mainstr������
    int j = 0; // patternstr������
    int index[100], k = 0; // ��¼ƥ���λ��

    while (i < mainlen) {
        if (patternstr[j] == mainstr[i]) {
            i++;
            j++;
        }

        if (j == patternlen) {
            index[k] = i - j; // �ҵ�ƥ���λ��
            k++;
            j = lps[j - 1]; // ����Ѱ����һ��ƥ��
        } else if (i < mainlen && patternstr[j] != mainstr[i]) {
            // mismatch after j matches
            if (j != 0) {
                j = lps[j - 1]; // ʹ�� lps �����ģʽ�ַ���
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
    
    // ȥ�������ַ����Ļ��з�
    mainstr[strcspn(mainstr, "\n")] = 0;
    patternstr[strcspn(patternstr, "\n")] = 0;

    KMPSearch(mainstr, patternstr);

    return 0;
}

