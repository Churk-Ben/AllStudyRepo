#include <iostream>
#include <algorithm>
#define N 50
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int a[N];
        for (int i = 0; i < n; i++)
            cin >> a[i];
        sort(a, a + n);
        int cnt = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if (a[i] == a[i + 1])
                cnt++;
            else{
                if (cnt % 2){
                    cout << "no" << endl;
                    break;
                }
                cnt = 0;
            }
            if (i == n - 2 && cnt % 2)
                cout << "no" << endl;
            if (i == n - 2 && cnt % 2 == 0)
                cout << "yes" << endl;
        }
    }
}