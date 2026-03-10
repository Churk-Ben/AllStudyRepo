#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int main()
{
    int n, k;
    while (cin >> n >> k)
    {
        vector<int> nums(n);
        memset(nums.data(), 0, sizeof(int) * n);
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if ((j + 1) % (i + 1) == 0)
                {
                    nums[j] = 1 - nums[j];
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (nums[i] == 0)
            {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
