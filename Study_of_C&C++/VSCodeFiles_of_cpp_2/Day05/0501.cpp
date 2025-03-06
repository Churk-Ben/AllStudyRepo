#include <iostream>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int a,b,c;
        cin >> a >> b >> c;
        cout << gcd(gcd(a,b),c) << endl;
    }
}
