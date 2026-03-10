#include <iostream>
using namespace std;
void fun(int &x, int &y)
{
    int z = x + y;
    x -= y;
    y = z;
}
void fun(int *x, int *y)
{
    int z = *x - *y;
    *x += *y;
    *y = z;
}
int main()
{
    int x = 20, y = 10;
    fun(x, y);
    cout << x << y << endl;
    fun(&x, &y);
    cout << x << y << endl;
    return 0;
}