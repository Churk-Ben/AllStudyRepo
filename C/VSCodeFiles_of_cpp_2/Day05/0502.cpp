#include <iostream>
#include <vector>
using namespace std;

// 模拟约瑟夫过程，返回是否满足条件
bool simulate(long long n, long long k, long long m)
{
    vector<long long> people(n, 1); // 1表示存活，0表示淘汰
    long long index = 0;
    long long count = 0;
    while (count < m)
    {
        long long step = 0;
        while (step < k)
        {
            if (people[index] == 1)
            {
                step++;
            }
            if (step < k)
            {
                index = (index + 1) % n;
            }
        }
        if (index < m)
        {
            return false; // 好人被淘汰，不满足条件
        }
        people[index] = 0;
        count++;
    }
    return true;
}

// 寻找最小的k
long long findMinK(long long m)
{
    long long k = 1;
    while (true)
    {
        if (simulate(2 * m, k, m))
        {
            return k;
        }
        k++;
    }
}

int main()
{
    long long m;
    cin >> m;
    long long k = findMinK(m);
    cout << k << endl;
    return 0;
}
