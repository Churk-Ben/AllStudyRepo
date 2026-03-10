#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

// 自己实现一个栈
typedef struct Stack
{
    int data[100];
    int top;
} Stack;

void init(Stack &st) // 初始化栈
{
    st.top = -1;
}

void push(Stack &st, int x) // 压栈
{
    st.data[++st.top] = x;
}

int pop(Stack &st) // 弹栈
{
    return st.data[st.top--];
}

bool empty(Stack &st) // 判断栈是否为空
{
    return st.top == -1;
}

int top(Stack &st) // 栈顶元素
{
    return st.data[st.top];
}

// 括号匹配
int is_match(string &s)
{
    Stack st;
    init(st);
    for (int i = 0; i < (int)s.size(); i++)
    {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
        {
            push(st, s[i]);
        }
        else
        {
            if (empty(st))
            {
                return 0;
            }
            int t = pop(st);
            if ((s[i] == ')' && t != '(') || (s[i] == ']' && t != '[') || (s[i] == '}' && t != '{'))
            {
                return 0;
            }
        }
    }
    return empty(st);
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    string s;
    cin >> s;
    if (is_match(s))
    {
        cout << "匹配" << endl;
    }
    else
    {
        cout << "此串括号匹配不合法" << endl;
    }
    return 0;
}