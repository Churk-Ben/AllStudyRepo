#include <stdio.h>
#include <string.h>

enum Role
{
    admin,
    student,
    teacher
};

typedef struct
{
    char username[20]; // �û���
    char password[20]; // ����
    enum Role type;    // �˻�����
} Account;

// ��������
void output(Account x[], int n); // ����˻�����x��n���˻���Ϣ�����У�������*�����ʾ

int main()
{
    Account x[] = {{"A1001", "123456", student},
                   {"A1002", "123abcdef", student},
                   {"A1009", "xyz12121", student},
                   {"X1009", "9213071x", admin},
                   {"C11553", "129dfg32k", teacher},
                   {"X3005", "921kfmg917", student}};
    int n;
    n = sizeof(x) / sizeof(Account);
    output(x, n);

    return 0;
}

// ������ĺ���output()ʵ��
// ���ܣ���������˻�����x��n���˻���Ϣ
//      ��ʾʱ�������ֶ�����ԭ������ͬ�ֶγ��ȵ�*�����ʾ
void output(Account x[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%-10s", x[i].username);
        for (int j = 0; j < (int)strlen(x[i].password); j++)
            printf("*");
        printf("\t");
        if (x[i].type == admin)
            printf("admin\n");
        else if (x[i].type == student)
            printf("student\n");
        else if (x[i].type == teacher)
            printf("teacher\n");
    }
}