#include <iostream>
#include <windows.h>
using namespace std;

// 实现一个循环链表
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    int size;
} CircleList;

void init(CircleList &cl) // 初始化循环链表
{
    cl.head = NULL;
    cl.size = 0;
}

int push(CircleList &cl, int x) // 入队
{
    Node *p = new Node;
    p->data = x;
    p->next = cl.head;
    cl.head = p;
    cl.size++;
}

int pop(CircleList &cl) // 出队
{
    if (cl.size == 0)
    {
        return -1;
    }
    Node *p = cl.head;
    int res = p->data;
    cl.head = p->next;
    cl.size--;
    delete p;
    return res;
}

int joseph(CircleList &cl, int m) // 约瑟夫问题
{
    CircleList queue;
    init(queue);
    for (int i = 0; i < cl.size; i++)
    {
        push(queue, cl.head->data);
        cl.head = cl.head->next;
    }
    while (queue.size > 1)
    {
        for (int i = 0; i < m - 1; i++)
        {
            int t = pop(queue);
            push(queue, t);
        }
        pop(queue);
    }
    return pop(queue);
}
