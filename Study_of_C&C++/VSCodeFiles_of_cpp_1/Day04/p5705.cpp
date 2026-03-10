#include <iostream>
using namespace std;

int main() {
    char c[6];
    cin>>c;
    for (int i = 0; i < 2; i++)
    {
        char temp = c[i];
        c[i] = c[4-i];
        c[4-i] = temp;
    }
    cout<<c<<endl;
    return 0;
}
