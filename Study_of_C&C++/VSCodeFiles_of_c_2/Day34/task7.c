#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[20];  // ����
    char phone[12]; // �ֻ���
    int vip;        // �Ƿ�Ϊ������ϵ�ˣ���ȡ1������ȡ0
} Contact;

int vip_cnt; // ͵͵ȫ����һ��������ϵ�˸���

// ��������
void set_vip_contact(Contact x[], int n, char name[]); // ���ý�����ϵ��
void output(Contact x[], int n);                       // ���x����ϵ����Ϣ
void display(Contact x[], int n);                      // ����ϵ�������ֵ���������ʾ��Ϣ��������ϵ��������ʾ
void sort(Contact x[], int n);                         // �������ֵ���������ϵ����Ϣ

#define N 10
int main()
{
    Contact list[N] = {
        {"����", "15510846604", 0},
        {"������", "15552933732", 0},
        {"�ض���", "18820725036", 0},
        {"��֪��", "18077702405", 0},
        {"�ǼҾ�", "18038747351", 0},
        {"�¿���", "17705843215", 0},
        {"���", "18853253914", 0},
        {"Ǯ��", "15547571923", 0},
        {"����", "18856659351", 0},
        {"����", "13230584477", 0},
    };

    int i;
    char name[20];

    printf("��ʾԭʼͨѶ¼��Ϣ: \n");
    output(list, N);

    printf("\n����Ҫ���õĽ�����ϵ�˸���: ");
    scanf("%d", &vip_cnt);

    printf("����%d��������ϵ������:\n", vip_cnt);
    for (i = 0; i < vip_cnt; ++i)
    {
        scanf("%s", name);
        set_vip_contact(list, N, name);
    }

    printf("\n��ʾͨѶ¼�б�:(�������ֵ�����������,������ϵ��������ʾ)\n");
    display(list, N);

    return 0;
}

// ���㺯��set_vip_contactʵ��
// ���ܣ�����ϵ������x�У���ϵ��������nameһ�����ˣ�����Ϊ������ϵ�ˣ�����Աvipֵ��Ϊ1��
void set_vip_contact(Contact x[], int n, char name[])
{
    for (int i = 0; i < N; i++)
    {
        if (strcmp(x[i].name, name) == 0)
        {
            x[i].vip = 1;
        }
    }
}

// ���㺯��displayʵ��
// ����: ��ʾ��ϵ������x�е���ϵ����Ϣ
//      �������ֵ���������ʾ, ������ϵ����ʾ����ǰ��
void display(Contact x[], int n)
{
    sort(x, n);
    output(x, n);
}

void output(Contact x[], int n)
{
    int i;

    for (i = 0; i < n; ++i)
    {
        printf("%-10s%-15s", x[i].name, x[i].phone);
        if (x[i].vip)
            printf("%5s", "*");
        printf("\n");
    }
}

void sort(Contact x[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (x[i].vip < x[j].vip)
            {
                Contact temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
    }
    for (int i = 0; i < vip_cnt; i++)
    {
        for (int j = i + 1; j < vip_cnt; j++)
        {
            if (strcmp(x[i].name, x[j].name) > 0)
            {
                Contact temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
    }
    for (int i = vip_cnt; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(x[i].name, x[j].name) > 0)
            {
                Contact temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
    }
}