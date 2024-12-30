#include <stdio.h>
#include <stdlib.h>
#define N 80

typedef struct FilmInfo
{
    char name[N];
    char director[N];
    char region[N];
    int year;
    struct FilmInfo *next;
} Film;

void output(Film *head);         // �������������Ϣ
Film *insert(Film *head, int n); // �������в���n����㣬����ͷָ��

int main()
{
    int n;      // �����
    Film *head; // ͷָ���������������е�һ���ڵ�ĵ�ַ

    head = NULL;
    printf("����ӰƬ��Ŀ: ");
    scanf("%d", &n);

    // �������в���n��ӰƬ��Ϣ
    head = insert(head, n);

    // �����������������ӰƬ��Ϣ
    printf("\n����ӰƬ��Ϣ����: \n");
    output(head);

    return 0;
}

// �������в���n����㣬�ӱ�ͷ���룬����ͷָ�����
Film *insert(Film *head, int n)
{
    int i;
    Film *p;

    for (i = 1; i <= n; ++i)
    {
        p = (Film *)malloc(sizeof(Film));
        printf("�������%d��ӰƬ��Ϣ: ", i);
        scanf("%s %s %s %d", p->name, p->director, p->region, &p->year);

        // �ѽ��ӱ�ͷ���뵽������
        p->next = head;
        head = p; // ����ͷָ�����
    }

    return head;
}

// �������������Ϣ
void output(Film *head)
{
    Film *p;

    p = head;
    while (p != NULL)
    {
        printf("%-20s %-20s %-20s %d\n", p->name, p->director, p->region, p->year);
        p = p->next;
    }
}