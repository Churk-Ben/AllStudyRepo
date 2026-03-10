#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node, *LinkList;

void freeList(LinkList L)
{
    Node *current = L;
    Node *nextNode;
    while (current != NULL)
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

void createList(LinkList *L, int arr[], int n)
{
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
    Node *current = *L;
    for (int i = 0; i < n; i++)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = arr[i];
        newNode->next = NULL;
        current->next = newNode;
        current = newNode;
    }
}

void printList(LinkList L, const char *name)
{
    printf("%s = ", name);
    Node *current = L->next;
    while (current != NULL)
    {
        printf("%d", current->data);
        if (current->next != NULL)
        {
            printf(",");
        }
        current = current->next;
    }
    printf("\n");
}

// 有序去重合并
void unionList(LinkList La, LinkList Lb)
{
    Node *pa = La->next;
    Node *pb = Lb->next;
    Node *prev_pa = La;

    while (pa != NULL && pb != NULL)
    {
        if (pa->data < pb->data)
        {
            prev_pa = pa;
            pa = pa->next;
        }
        else if (pa->data > pb->data)
        {
            Node *newNode = (Node *)malloc(sizeof(Node));
            newNode->data = pb->data;
            newNode->next = pa;
            prev_pa->next = newNode;
            prev_pa = newNode;
            pb = pb->next;
        }
        else
        {
            prev_pa = pa;
            pa = pa->next;
            pb = pb->next;
        }
    }

    if (pb != NULL)
    {
        prev_pa->next = pb;
    }

    Lb->next = NULL;
}

// 有序不去重合并
void mergeList(LinkList La, LinkList Lb, LinkList *Lc)
{
    *Lc = (LinkList)malloc(sizeof(Node));
    (*Lc)->next = NULL;
    Node *pc = *Lc;
    Node *pa = La->next;
    Node *pb = Lb->next;

    while (pa != NULL && pb != NULL)
    {
        if (pa->data <= pb->data)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = (pa != NULL) ? pa : pb;

    La->next = NULL;
    Lb->next = NULL;
}

// 去重
void set(LinkList L)
{
    if (L == NULL || L->next == NULL)
        return;
    Node *current = L->next;
    while (current != NULL && current->next != NULL)
    {
        if (current->data == current->next->data)
        {
            Node *temp = current->next;
            current->next = temp->next;
            free(temp);
        }
        else
        {
            current = current->next;
        }
    }
}

int main()
{
    // 设置控制台输出代码页为UTF-8以正确显示中文字符
    SetConsoleOutputCP(65001);

    // 初始数据
    int arr_a[] = {1, 2, 3, 4, 5};
    int arr_b[] = {2, 4, 6, 8, 10};
    LinkList La, Lb;
    createList(&La, arr_a, 5);
    createList(&Lb, arr_b, 5);

    printf("初始链表:\n");
    printList(La, "La");
    printList(Lb, "Lb");
    printf("\n");

    // 有序去重合并
    unionList(La, Lb);
    printf("有序去重合并后:\n");
    printList(La, "new La");
    printf("\n");
    free(Lb);

    // 有序不去重合并
    int arr_b_new[] = {2, 6, 8, 9, 11, 15, 20};
    LinkList Lb_new, Lc;
    createList(&Lb_new, arr_b_new, 7);

    int arr_a_new[] = {1, 2, 3, 4, 5, 6, 8, 10};
    LinkList La_new;
    createList(&La_new, arr_a_new, 8);

    printf("有序不去重合并前:\n");
    printList(La_new, "La_new");
    printList(Lb_new, "Lb_new");

    mergeList(La_new, Lb_new, &Lc);
    printf("有序不去重合并后:\n");
    printList(Lc, "Lc");
    printf("\n");
    free(La_new);
    free(Lb_new);

    // 集合化
    set(Lc);
    printf("集合化:\n");
    printList(Lc, "Lc_set");
    printf("\n");
    freeList(La);
    freeList(Lc);

    return 0;
}