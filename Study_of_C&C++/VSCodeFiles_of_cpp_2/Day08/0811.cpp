#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(6);
    vector<int> b(6);
    while (n--)
    {
        for (int i = 0; i < 6; ++i)
        {
            cin >> a[i];
        }
        copy(a.begin(), a.end(), b.begin());
        int cnt = 0;

        // 开始装箱
        cnt += b[5]; // 6x6的盒子装箱完毕
        a[5] = 0;
        copy(a.begin(), a.end(), b.begin());
        for (int m : b)
            cout << m << " ";
        cout << endl;

        cnt += b[4]; // 5x5的盒子装箱完毕
        a[4] = 0;
        int temp = b[4] * 11;
        if (a[0] >= temp)
            a[0] -= temp;
        else
            a[0] = 0;
        copy(a.begin(), a.end(), b.begin());
        for (int m : b)
            cout << m << " ";
        cout << endl;

        cnt += b[3]; // 4x4的盒子装箱完毕
        a[3] = 0;
        temp = b[3] * 5;
        if (a[1] >= temp)
            a[1] -= temp;
        else
        {
            a[1] = 0;
            temp = (b[3] % 5) ? (5 - (b[3] % 5)) * 4 : 0;
            if (a[0] >= temp)
                a[0] -= temp;
            else
                a[0] = 0;
        }
        copy(a.begin(), a.end(), b.begin());
        for (int m : b)
            cout << m << " ";
        cout << endl;

        cnt += b[2] / 4 + (b[2] % 4 > 0); // 3x3的盒子装箱完毕
        a[2] = 0;
        temp = b[2] % 4;
        switch (temp)
        {
        case 1:
            if (a[1] >= 5)
                a[1] -= 5;
            else
            {
                if (a[0] >= (5 - a[1]) * 4)
                    a[0] -= (5 - a[1]) * 4;
                else
                    a[0] = 0;
                a[1] = 0;
            }
            if (a[0] >= 7)
                a[0] -= 7;
            else
                a[0] = 0;
            break;
        case 2:
            if (a[1] >= 3)
                a[1] -= 3;
            else
            {
                if (a[0] >= (3 - a[1]) * 4)
                    a[0] -= (3 - a[1]) * 4;
                else
                    a[0] = 0;
                a[1] = 0;
            }
            if (a[0] >= 6)
                a[0] -= 6;
            else
                a[0] = 0;
            break;
        case 3:
            if (a[1] >= 1)
                a[1] -= 1;
            else
            {
                if (a[0] >= (1 - a[1]) * 4)
                    a[0] -= (1 - a[1]) * 4;
                else
                    a[0] = 0;
                a[1] = 0;
            }
            if (a[0] >= 5)
                a[0] -= 5;
            else
                a[0] = 0;
            break;
        default:
            break;
        }
        copy(a.begin(), a.end(), b.begin());
        for (int m : b)
            cout << m << " ";
        cout << endl;

        // 以下装 2x2 和 1x1 的盒子
        cnt += b[1] / 9 + (b[1] % 9 > 0); // 2x2的盒子装箱完毕
        temp = b[1] % 9;
        if (temp > 0)
        {
            if (a[0] >= (9 - temp) * 4)
                a[0] -= (9 - temp) * 4;
            else
                a[0] = 0;
        }
        a[1] = 0;
        copy(a.begin(), a.end(), b.begin());
        for (int m : b)
            cout << m << " ";
        cout << endl;

        cnt += b[0] / 36 + (b[0] % 36 > 0); // 1x1的盒子装箱完毕
        a[0] = 0;
        copy(a.begin(), a.end(), b.begin());
        for (int m : b)
            cout << m << " ";
        cout << endl;

        cout << cnt << endl;
    }
    return 0;
}
