#include <stdio.h>
#include <string.h>

int main()
{
    char mainstr[100], patternstr[100];
    fgets(mainstr, sizeof(mainstr), stdin);
    fgets(patternstr, sizeof(patternstr), stdin);
    
    // ȥ�����з�
    mainstr[strcspn(mainstr, "\n")] = '\0';
    patternstr[strcspn(patternstr, "\n")] = '\0';
    
    int j = 0, index[100];
    int mainstrLen = strlen(mainstr);
    int patternstrLen = strlen(patternstr);
    
    for (int i = 0; i <= mainstrLen - patternstrLen; i++)
    {
        int t = 0;
        while (t < patternstrLen && mainstr[i + t] == patternstr[t])
        {
            t++;
        }
        if (t == patternstrLen) // ���t����ģʽ�ַ����ĳ��ȣ���ʾ�ҵ���ƥ��
        {
            index[j] = i;
            j++;
        }
    }

    printf("Index of pattern in main string are: ");
    for (int i = 0; i < j; i++)
    {
        printf("%d ", index[i]);
    }
    
    return 0;
}
