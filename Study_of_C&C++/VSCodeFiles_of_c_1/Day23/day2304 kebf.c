#include <stdio.h>
#include <string.h>

int main()
{
    // ���������ַ���
    char ms[100], ps[100];
    fgets(ms, sizeof(ms), stdin);
    fgets(ps, sizeof(ps), stdin);

    // ȥ�����з�
    ms[strcspn(ms, "\n")] = '\0';
    ps[strcspn(ps, "\n")] = '\0';

    int j = 0, index[100];
    int msL = strlen(ms);
    int psL = strlen(ps);
    // �㷨ʵ��
    for (int i = 0; i <= msL - psL; )
    {
        if ((msL - i) < psL)
            break;
        int t = 0;
        while (t < psL && ms[i + t] == ps[t])
            t++;
        if (t == psL)
            index[j++] = i;
        i += (t > 0) ? t : 1;
    }
    // ������
    if (j > 0)
        for (int i = 0; i < j; i++)
            printf("%d ", index[i]);
    else
        printf("None");
    printf("\n");

    return 0;
}