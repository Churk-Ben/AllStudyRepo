#include <iostream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
    int n, w, s;
    while (cin >> n)
    {
        list<string> l;
        for (int i = 0; i < n; i++)
        {
            string x;
            cin >> x;
            l.push_back(x);
        }

        scanf("%d,%d", &w, &s);
        int cnt = 0;
        list<string>::iterator it = l.begin();
        advance(it, w - 1);
        while (!l.empty())
        {
            cnt++;
            if (it == l.end())
                it = l.begin();
            if (cnt == s)
            {
                cout << *it << endl;
                it = l.erase(it);
                cnt = 0;
                if (it == l.end())
                    it = l.begin();
            }
            else
            {
                it++;
            }
        }
    }
    return 0;
}
