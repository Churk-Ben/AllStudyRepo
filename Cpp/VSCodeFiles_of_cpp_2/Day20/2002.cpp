#include <iostream>
using namespace std;

int b = 0;
void fun(int a)
{
    int b = 1;
    static int c = 1;
    ++a;
    ++b;
    ++c;
    cout << a << b << c << endl;
}
int main()
{
    int x = 1, i;
    for (i = 5; i < 8; i++)
        fun(x);
    return 0;
}