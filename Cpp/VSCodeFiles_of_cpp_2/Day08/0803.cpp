#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void sortInter(vector<int> &start, vector<int> &end)
{
    for (size_t i = 0; i < start.size() - 1; ++i)
    {
        for (size_t j = 0; j < start.size() - 1 - i; ++j)
        {
            if (start[j] > start[j + 1])
            {
                swap(start[j], start[j + 1]);
                swap(end[j], end[j + 1]);
            }
        }
    }
}

int mergeInter(vector<int> &start, vector<int> &end)
{
    int cStart = start[0];
    int cEnd = end[0];
    int cnt = 0;

    for (size_t i = 1; i < start.size(); ++i)
    {
        if (cEnd < start[i])
        {
            cnt += (cEnd - cStart + 1);
            cStart = start[i];
            cEnd = end[i];
        }
        else if (cEnd < end[i])
        {
            cEnd = end[i];
        }
    }
    cnt += (cEnd - cStart + 1);
    return cnt;
}

int main()
{
    int l, n;
    cin >> l >> n;
    l++;

    vector<int> start(n);
    vector<int> end(n);

    for (int i = 0; i < n; ++i)
        cin >> start[i] >> end[i];

    sortInter(start, end);
    int t = mergeInter(start, end);
    cout << l - t << endl;

    return 0;
}
