#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 高精度加法
vector<int> add(vector<int> &A, vector<int> &B)
{
    vector<int> C;
    int carry = 0; // 进位
    for (int i = 0; i < A.size() || i < B.size(); i++)
    {
        if (i < A.size())
            carry += A[i];
        if (i < B.size())
            carry += B[i];
        C.push_back(carry % 10);
        carry /= 10;
    }
    if (carry)
        C.push_back(carry); // 如果最后还有进位
    return C;
}

int main()
{
    string a, b;
    cin >> a >> b;
    vector<int> A, B;
    // 将字符串逆序存储到数组中
    for (int i = a.size() - 1; i >= 0; i--)
        A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i--)
        B.push_back(b[i] - '0');
    // 计算加法
    vector<int> C = add(A, B);
    // 输出结果
    for (int i = C.size() - 1; i >= 0; i--)
        cout << C[i];
    cout << endl;
    return 0;
}
