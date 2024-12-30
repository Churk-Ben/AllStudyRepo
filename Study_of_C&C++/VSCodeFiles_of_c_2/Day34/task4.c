#include <stdio.h>
#define N 10

typedef struct
{
    char isbn[20];      // isbn��
    char name[80];      // ����
    char author[80];    // ����
    double sales_price; // �ۼ�
    int sales_count;    // ���۲���
} Book;

void output(Book x[], int n);
void sort(Book x[], int n);
double sales_amount(Book x[], int n);

int main()
{
    Book x[N] = {{"978-7-5327-6082-4", "�Ž�֮��", "���ɵ�.��", 42, 51},
                 {"978-7-308-17047-5", "�����밮֮�أ�����ɫ�м�", "��Ҳ��", 49, 30},
                 {"978-7-5404-9344-8", "�׶���", "������̩��", 68, 27},
                 {"978-7-5447-5246-6", "��������������", "�ص½�", 35, 90},
                 {"978-7-5722-5475-8", "оƬ��ʷ", "����", 74.9, 49},
                 {"978-7-5133-5750-0", "����ս��", "������.J.����˹", 128, 42},
                 {"978-7-2011-4617-1", "���羡ͷ�Ŀ��ȹ�", "Լ����ʷ���ջ�", 22.5, 44},
                 {"978-7-5133-5109-6", "���������", "Ӣ��δ�����漯��", 118, 42},
                 {"978-7-1155-0509-5", "����Ŀ�ʼ:��������ı�Դ", "��ά��������", 37.5, 55},
                 {"978-7-229-14156-1", "ԴȪ", "��.����", 84, 59}};

    printf("ͼ����������(�����۲���): \n");
    sort(x, N);
    output(x, N);

    printf("\nͼ�������ܶ�: %.2f\n", sales_amount(x, N));

    return 0;
}

// �����㣺����output()ʵ��
void output(Book x[], int n)
{
    printf("ISBN��\t\t\t ����\t\t\t\t ����\t\t\t �ۼ�\t ���۲���\n");
    for (int i = 0; i < n; i++)
    {
        printf("%-15s\t %-25s\t %-20s\t %-5g\t %-5d\n", x[i].isbn, x[i].name, x[i].author, x[i].sales_price, x[i].sales_count);
    }
    // ���������������
}

// �����㣺����sort()ʵ��
void sort(Book x[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (x[i].sales_count < x[j].sales_count)
            {
                Book temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
    }
}

// �����㣺����sales_amount()ʵ��
double sales_amount(Book x[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += x[i].sales_price * x[i].sales_count;
    }
    return sum;
}
