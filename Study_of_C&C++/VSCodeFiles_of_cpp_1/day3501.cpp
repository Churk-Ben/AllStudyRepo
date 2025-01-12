#include <iostream>
#include <vector>
using namespace std;

// 将整数转换为数字向量
vector<int> shuzuhua(int a)
{
    int temp = a, length = 1;
    while ((temp /= 10) != 0)
        length++;
    vector<int> result(length);
    for (int i = length - 1; i >= 0; --i)
    {
        result[i] = a % 10;
        a /= 10;
    }
    return result;
}

// 判断向量中的元素是否重复
bool panduan(const vector<int> &a)
{
    for (size_t i = 0; i < a.size(); ++i)
    {
        for (size_t j = i + 1; j < a.size(); ++j)
        {
            if (a[i] == a[j])
                return false;
        }
    }
    return true;
}

int main()
{
    for (int i = 100; i < 333; ++i)
    {
        // 获取各个数字向量
        vector<int> v1 = shuzuhua(i);
        vector<int> v2 = shuzuhua(2 * i);
        vector<int> v3 = shuzuhua(3 * i);

        if (panduan(v1))
        {
            // 合并向量
            v1.insert(v1.end(), v2.begin(), v2.end());
            v1.insert(v1.end(), v3.begin(), v3.end());

            if (panduan(v1))
            {
                // 输出结果
                for (size_t j = 0; j < v1.size(); ++j)
                {
                    cout << v1[j];
                    if ((i + 1) % 3 == 0 && j < v1.size() - 1)
                    {
                        cout << " ";
                    }
                }
                cout << endl;
            }
        }
    }

    return 0;
}