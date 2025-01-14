#include <iostream>
using namespace std;

int main() {
    char ch;
    cin >> ch;

    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 3 - i - 1; j++) {
            cout << " ";
        }

        for (int k = 0; k < 2 * i + 1; k++) {
            cout << ch;
        }

        cout << endl;
    }

    return 0;
}
