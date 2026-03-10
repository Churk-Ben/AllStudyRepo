#include <iostream>

int b;

void fun(int a)
{
    int b = 1;
    static int c = 1;
    ++a, ++b, ++c;
    std::cout << a << b << c << '\n';
}

int main()
{
    for (int i = 0; i < 2; i++)
        fun(i);
}