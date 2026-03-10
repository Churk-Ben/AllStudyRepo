#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int main()
{
    int Q, op, x;
    set<int> s;
    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        cin >> op >> x;
        switch (op)
        {
        case 1:
            s.insert(x);
            break;

        case 2:
            if (s.count(x))
                s.erase(x);
            break;

        case 3:
            auto it = s.lower_bound(x);
            if (it != s.end())
                cout << *it << endl;
            else
                cout << -1 << endl;
            break;
        }
    }

    return 0;
}