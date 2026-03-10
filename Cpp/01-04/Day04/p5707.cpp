#include <iostream>
using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
    int mins = a / b + (a % b != 0) + 10;
    int t = 32 * 60 - mins;
    int m = t % 60;
    int h = (t / 60) % 24;
    printf("%02d:%02d\n", h, m);
    return 0;
}
