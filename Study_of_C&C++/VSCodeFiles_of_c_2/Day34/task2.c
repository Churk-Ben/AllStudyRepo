#include <stdio.h>
#include <string.h>
#define N 10
#define M 80

typedef struct
{
    char name[M];   // ����
    char author[M]; // ����
} Book;

int main()
{
    Book x[N] = {{"��һ�Ű��ġ�", "����.������"},
                 {"�����������硷", "������"},
                 {"�����յ����硷", "˹�ٷ�.������"},
                 {"������ʮ���꡷", "������"},
                 {"��һֻ�������е���", "��С��"},
                 {"������¶���", "�����˹"},
                 {"������ʮ�ֽ�84�š�", "����.��ܽ"},
                 {"��ֻ�Ǻ��ӡ�", "����.ʷ��˹"},
                 {"�����桷", "ëķ"},
                 {"����Ĭ�Ĵ������", "��С��"}};
    Book *ptr;
    int i;
    char author[M];
    int found;

    // ʹ��ָ������ṹ������
    printf("-------------------����ͼ����Ϣ-------------------\n");
    for (ptr = x; ptr < x + N; ++ptr)
        printf("%-30s%-30s\n", ptr->name, ptr->author);

    // ����ָ�����ߵ�ͼ��
    printf("\n-------------------�����߲�ѯͼ��-------------------\n");
    printf("����������: ");
    gets(author);
    found = 0;
    for (ptr = x; ptr < x + N; ++ptr)
        if (strcmp(ptr->author, author) == 0)
        {
            found = 1;
            printf("%-30s%-30s\n", ptr->name, ptr->author);
        }

    if (!found)
        printf("��δ��¼�������鼮!\n");

    return 0;
}