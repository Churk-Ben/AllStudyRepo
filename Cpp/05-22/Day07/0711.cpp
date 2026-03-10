#include <iostream>
#include <vector>
using namespace std;

bool func(int m, int k)
{
    vector<int> circle(2 * m, 0);
    fill(circle.begin(), circle.begin() + m, 1);

    int i = 0, cnt = 2 * m;
    while (cnt > m)
    {
        int t = (k - 1) % cnt;
        i = (i + t) % cnt;
        if (circle[i] == 1)
            return false;
        copy(circle.begin() + i + 1, circle.end(), circle.begin() + i);
        cnt--;
    }
    return true;
}

int main()
{
    int m;
    while (cin >> m)
    {
        int k = 1;
        while (!func(m, k))
            k++;
        cout << k << endl;
    }
    return 0;
}
