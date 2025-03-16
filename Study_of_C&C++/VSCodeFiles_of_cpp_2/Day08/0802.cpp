// 高精度模板
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

int compare(string a, string b)
{
    while (a.size() > 1 && a[0] == '0')
        a.erase(0, 1);
    while (b.size() > 1 && b[0] == '0')
        b.erase(0, 1);

    if (a.size() > b.size())
        return 1;
    if (a.size() < b.size())
        return -1;

    for (size_t i = 0; i < a.size(); ++i)
    {
        if (a[i] > b[i])
            return 1;
        if (a[i] < b[i])
            return -1;
    }
    return 0;
}

// 将字符串逆序存储到数组中
vector<int> adjust(string x)
{
    vector<int> res;
    for (int i = x.size() - 1; i >= 0; i--)
        res.push_back(x[i] - '0');
    return res;
}

// 高精度加法
string add(string a, string b, int scale)
{
    vector<int> A, B;
    vector<char> C;
    A = adjust(a);
    B = adjust(b);
    int carry = 0;
    for (int i = 0; i < (int)A.size() || i < (int)B.size(); i++)
    {
        if (i < (int)A.size())
            carry += A[i];
        if (i < (int)B.size())
            carry += B[i];
        C.push_back((char)(carry % scale) + '0');
        carry /= scale;
    }
    if (carry)
        C.push_back((char)carry + '0');
    reverse(C.begin(), C.end());
    return string(C.begin(), C.end());
}

// 高精度减法
string sub(string a, string b, int scale)
{
    vector<int> A, B;
    vector<char> C;
    A = adjust(a);
    B = adjust(b);
    if (compare(a, b) < 0)
    {
        swap(A, B);
        C.push_back('-');
    }
    int borrow = 0;
    for (int i = 0; i < (int)A.size(); i++)
    {
        int diff = A[i] - borrow;
        if (i < (int)B.size())
            diff -= B[i];
        if (diff < 0)
        {
            diff += scale;
            borrow = 1;
        }
        else
            borrow = 0;
        C.push_back('0' + diff);
    }
    while (C.size() > 1 && C.back() == '0')
        C.pop_back();
    if (C[0] == '-')
        reverse(C.begin() + 1, C.end());
    else
        reverse(C.begin(), C.end());
    return string(C.begin(), C.end());
}

// 高精度浮点数减法
string fsub(string a, string b)
{
    string Ai, Bi, Af = "0", Bf = "0", Ci, Cf;
    size_t pos;
    int neg = 0;

    pos = a.find('.');
    if (pos != string::npos)
    {
        Ai = a.substr(0, pos);
        Af = a.substr(pos + 1, a.size() - pos - 1);
    }
    else
        Ai = a;

    pos = b.find('.');
    if (pos != string::npos)
    {
        Bi = b.substr(0, pos);
        Bf = b.substr(pos + 1, b.size() - pos - 1);
    }
    else
        Bi = b;
    if (compare(Ai, Bi) < 0)
    {
        swap(Ai, Bi);
        swap(Af, Bf);
        neg = 1;
    }
    int m = max(Af.size(), Bf.size());
    Af.insert(Af.end(), m - Af.size(), '0');
    Bf.insert(Bf.end(), m - Bf.size(), '0');
    Af.insert(Af.begin(), 1, '1');
    Cf = sub(Af, Bf, 10);
    int borrow = 1;
    if ((int)Cf.size() > m)
    {
        borrow = 0;
        Cf = Cf.substr(1);
    }
    Ci = sub(Ai, Bi, 10);
    if (borrow)
        Ci = sub(Ci, to_string(borrow), 10);
    if (Ci.size() > 1 && Ci[0] == '0')
        Ci.erase(0, Ci.find_first_not_of('0'));
    while (Cf.size() > 1 && Cf.back() == '0')
        Cf.pop_back();
    if (neg)
        Ci = "-" + Ci;

    return Ci + "." + Cf;
}

int main()
{
    string a, b;
    cin >> a >> b;
    string C = fsub(a, b);
    cout << C << endl;
    return 0;
}
