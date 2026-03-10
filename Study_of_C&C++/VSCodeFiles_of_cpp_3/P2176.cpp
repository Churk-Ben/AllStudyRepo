#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int main()
{
    int Q, op, x;
    multiset<int> s;
    cin >> Q;
    auto it = s.begin();
    for (int i = 0; i < Q; i++)
    {
        cin >> op >> x;
        switch (op)
        {
        case 1:
            s.insert(x);
            break;

        case 2:
            it = s.find(x);
            if (it != s.end())
                s.erase(it);
            break;

        case 3:
            it = s.upper_bound(x);
            if (it != s.end())
                cout << *it << endl;
            else
                cout << -1 << endl;
            break;
        }
    }

    return 0;
}