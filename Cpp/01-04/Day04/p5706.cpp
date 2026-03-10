#include <iostream>
using namespace std;

int main() {
    int n;
    double t;
    cin >> t >> n;
    double avg = t/n;
    printf("%.3lf\n", avg);
    cout << n*2 << endl;
}