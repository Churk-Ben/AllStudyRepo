#include <stdio.h>
#include <string.h>

int main()
{
    char ms[100], ps[100];
    fgets(ms, sizeof(ms), stdin);
    fgets(ps, sizeof(ps), stdin);

    // ȥ�����з�
    ms[strcspn(ms, "\n")] = '\0';
    ps[strcspn(ps, "\n")] = '\0';

    int j = 0, index[100];
    int msL = strlen(ms);
    int psL = strlen(ps);

    // ������ַ�������С��ģʽ�ַ������ȣ�ֱ�ӷ���
    if (msL < psL) {
        printf("Index of pattern in main string are: None\n");
        return 0;
    }

    for (int i = 0; i <= msL - psL; ) // ���ѭ�������� i���������ڲ����
    {
        // ÿ��ƥ��ǰ���� t
        int t = 0;
        while (t < psL && ms[i + t] == ps[t])
        {
            t++;
        }
        
        // ���ģʽ����ȫƥ��
        if (t == psL)
        {
            index[j] = i; // ��¼ƥ�����ʼ����
            j++;

            // ֱ�������Ѿ��ҵ���ƥ�䲿��
            i += t; // ����i��������ǰƥ����ַ�
        }
        else
        {
            i++; // ���û��ƥ��ɹ�, �ƶ� i ��������
        }
    }

    printf("Index of pattern in main string are: ");
    if (j > 0) {
        for (int i = 0; i < j; i++)
        {
            printf("%d ", index[i]);
        }
    } else {
        printf("None"); // ���û���ҵ�ƥ��
    }
    
    printf("\n"); // ��ӻ��з����������

    return 0;
}
