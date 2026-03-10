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

void output(Film *head);         // 遍历输出链表信息
Film *insert(Film *head, int n); // 向链表中插入n个结点，返回头指针

int main()
{
    int n;      // 结点数
    Film *head; // 头指针变量，存放链表中第一个节点的地址

    head = NULL;
    printf("输入影片数目: ");
    scanf("%d", &n);

    // 向链表中插入n部影片信息
    head = insert(head, n);

    // 遍历输出链表中所有影片信息
    printf("\n所有影片信息如下: \n");
    output(head);

    return 0;
}

// 向链表中插入n个结点，从表头插入，返回头指针变量
Film *insert(Film *head, int n)
{
    int i;
    Film *p;

    for (i = 1; i <= n; ++i)
    {
        p = (Film *)malloc(sizeof(Film));
        printf("请输入第%d部影片信息: ", i);
        scanf("%s %s %s %d", p->name, p->director, p->region, &p->year);

        // 把结点从表头插入到链表中
        p->next = head;
        head = p; // 更新头指针变量
    }

    return head;
}

// 遍历输出链表信息
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