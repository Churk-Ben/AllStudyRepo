#include <iostream>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

int main()
{
    int Q, op;
    long x;
    string S;
    map<string, long> m;

    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        cin >> op >> S;
        switch (op)
        {
        case 1:
            cin >> x;
            m[S] += x;
            break;

        case 2:
            cin >> x;
            if (m[S] >= x)
            {
                m[S] -= x;
                cout << m[S] << endl;
            }
            else
            {
                cout << -1 << endl;
            }
            break;

        case 3:
            cout << m[S] << endl;
            break;
        }
    }

    return 0;
}