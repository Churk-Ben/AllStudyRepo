#include <iostream>
using namespace std;
class T
{
public:
    static int x;
};
int T::x = 1;
int main()
{
    T a, b;
    a.x = 10;
    b.x = 20;
    cout << "a.x=" << a.x << endl;
    cout << "b.x=" << b.x << endl;
    cout << "T::x=" << T::x << endl;
    return 0;
}