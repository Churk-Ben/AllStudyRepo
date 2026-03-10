#include <iostream>
using namespace std;

int main()
{
    int a, x;
    for (a = 0, x = 0; !x && a <= 10; a++)
        a++;
    cout << a << endl;
    return 0;
}