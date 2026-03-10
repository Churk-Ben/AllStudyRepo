#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

string MAP[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};

// 自己实现一个栈
typedef struct Stack
{
	int data[100];
	int top;
} Stack;

// 初始化栈
void init(Stack &st)
{
	st.top = -1;
}

// 压栈
void push(Stack &st, int x)
{
	st.data[++st.top] = x;
}

// 弹栈
int pop(Stack &st)
{
	return st.data[st.top--];
}

// 判断栈是否为空
bool empty(Stack &st)
{
	return st.top == -1;
}

// 进制转换
string num_transfer(string num, int p)
{
	Stack pn;
	init(pn);
	do
	{
		push(pn, stoi(num) % p);
		num = to_string(stoi(num) / p);
	} while (stoi(num));
	string pnum = "";
	while (!empty(pn))
	{
		pnum += MAP[pop(pn)];
	}
	return pnum;
}

// 回文字符串
int str_palindrome(string &str)
{
	Stack st;
	init(st);
	for (char c : str)
	{
		push(st, c);
	}

	for (char c : str)
	{
		if (pop(st) != c)
			return 0;
	}
	return 1;
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	int n, p;
	cout << "输入一个整数" << endl;
	cin >> n;
	cout << "输入进制" << endl;
	cin >> p;
	string pn = num_transfer(to_string(n), p);
	cout << pn << endl;

	string s;
	cout << "输入一个字符串" << endl;
	cin >> s;
	if (str_palindrome(s))
		cout << "Right" << endl;
	else
		cout << "Wrong" << endl;

	return 0;
}
