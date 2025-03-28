#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(6);
    while (n--)
    {
        cin >> a[0] >> a[1] >> a[2] >> a[3] >> a[4] >> a[5];
        int cnt = a[5] + a[4] + a[3];
        a[0] = (a[4] * 11 > a[0]) ? 0 : (a[0] - a[4] * 11);
        a[1] = (a[3] * 5 > a[1]) ? 0 : (a[1] - a[3] * 5);
        if (a[0] > 0 && a[1] == 0)
        {
            int temp = a[1] - a[3] * 5;
            a[0] = (temp * 4 > a[0]) ? 0 : (a[0] - temp * 4);
        }
        if (a[0] == 0 && a[1] == 0 && a[2] == 0)
        {
            cout << cnt << endl;
            continue;
        }
        // 至此，4x4 5x5 6x6的盒子都已经装箱，还剩1x1 2x2 3x3的盒子，并且所有箱子已经装满
        cnt += a[2] / 4 + 1;
        int temp = a[2] %= 4;
        switch (temp)
        {
        case 1:
            a[1] = (5 > a[1]) ? 0 : (a[1] - 5);
            a[0] = (7 > a[0]) ? 0 : (a[0] - 7);
            if (a[0] > 0 && a[1] == 0)
            {
                int temp2 = a[1] - a[3] * 5;
                a[0] = (temp2 * 4 > a[0]) ? 0 : (a[0] - temp2 * 4);
            }
            break;
        case 2:
            a[1] = (3 > a[1]) ? 0 : (a[1] - 3);
            a[0] = (6 > a[0]) ? 0 : (a[0] - 6);
            break;
        case 3:
            a[0] = (1 > a[0]) ? 0 : (a[0] - 1);
            a[0] = (5 > a[0]) ? 0 : (a[0] - 5);
            break;
        default:
            break;
        }
    }
} // unsolved