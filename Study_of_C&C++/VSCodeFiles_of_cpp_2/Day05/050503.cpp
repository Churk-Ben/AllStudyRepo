#include <iostream>
#include <vector>
using namespace std;

// 比较两个数的大小，A >= B 返回 true
bool cmp(vector<int> &A, vector<int> &B) {
    if (A.size() != B.size()) return A.size() > B.size();
    for (int i = A.size() - 1; i >= 0; i--) {
        if (A[i] != B[i]) return A[i] > B[i];
    }
    return true;
}

// 高精度减法
vector<int> sub(vector<int> &A, vector<int> &B) {
    vector<int> C;
    int carry = 0; // 借位
    for (int i = 0; i < A.size(); i++) {
        carry = A[i] - carry;
        if (i < B.size()) carry -= B[i];
        C.push_back((carry + 10) % 10);
        if (carry < 0) carry = 1;
        else carry = 0;
    }
    // 去除前导0
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

int main() {
    string a, b;
    cin >> a >> b;
    vector<int> A, B;
    // 将字符串逆序存储到数组中
    for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i--) B.push_back(b[i] - '0');
    // 判断 A 是否大于等于 B
    if (cmp(A, B)) {
        vector<int> C = sub(A, B);
        // 输出结果
        for (int i = C.size() - 1; i >= 0; i--) cout << C[i];
    } else {
        vector<int> C = sub(B, A);
        // 输出结果，前面加上负号
        cout << "-";
        for (int i = C.size() - 1; i >= 0; i--) cout << C[i];
    }
    cout << endl;
    return 0;
}
