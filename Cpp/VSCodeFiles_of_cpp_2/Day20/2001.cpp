#include <iostream>
using namespace std;

int i;
void fun(int a)
{
    int b = 1;
    static int c = 1;
    ++i;
    ++a;
    ++b;
    ++c;
    cout << i << a << b << c << endl;
}
int main()
{
    int i;
    for (i = 1; i < 3; i++)
    {
        fun(i);
        cout << endl;
    }
    return 0;
}