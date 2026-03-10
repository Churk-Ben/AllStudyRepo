#include <iostream>
using namespace std;

// 手写一个循环队列
const int N = 7;

typedef struct CQueue
{
    int data[N];
    int front;
    int rear;
    int count;
} CQueue;

void init(CQueue &q)
{
    q.front = 0;
    q.rear = 0;
    q.count = 0;
}

void push(CQueue &q, int val)
{
    if (q.count == N)
        return; // 队列满
    q.data[q.rear] = val;
    q.rear = (q.rear + 1) % N;
    ++q.count;
}

void pop(CQueue &q)
{
    if (q.count == 0)
        return; // 队列空
    q.front = (q.front + 1) % N;
    --q.count;
}

void print(CQueue &q)
{
    for (int i = 0; i < q.count; ++i)
    {
        cout << q.data[(q.front + i) % N] << " ";
    }
    cout << endl;
}

int main()
{
    CQueue q;
    init(q);
    push(q, 7);
    push(q, 5);
    push(q, 3);
    push(q, 9);
    push(q, 2);
    push(q, 4);
    pop(q);
    pop(q);
    pop(q);
    push(q, 15);
    push(q, 18);

    print(q);
    return 0;
}