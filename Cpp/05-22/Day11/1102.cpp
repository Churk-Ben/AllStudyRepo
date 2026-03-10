#include <iostream>
#include <complex>
#include <cmath>
using std::cout;
using std::endl;

template <class T>
void swap(T &x, T &y)
{
    T t;
    t = x, x = y, y = t;
}

template <class T>
void test_swap(T &x, T &y)
{
    cout << "x = " << x << " , y = " << y << endl;
    swap(x, y);
    cout << "After swap:\n";
    cout << "x = " << x << " , y = " << y << endl;
}

int main()
{
    int x1 = 3, y1 = 4;
    test_swap(x1, y1);
    double x2 = 3.3, y2 = 4.4;
    test_swap(x2, y2);
    char x3 = 'Y', y3 = 'N';
    test_swap(x3, y3);
    std ::string x4{"YES"}, y4{"NO"};
    test_swap(x4, y4);
    return 0;
}