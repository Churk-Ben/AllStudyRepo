#include <iostream>
#include <vector>
using namespace std;

// 模拟约瑟夫过程，返回是否满足条件
bool simulate(int n, int k, int m) {
    vector<int> people(n, 1); // 1表示存活，0表示淘汰
    int index = 0;
    int count = 0;
    while (count < m) {
        int step = 0;
        while (step < k) {
            if (people[index] == 1) {
                step++;
            }
            if (step < k) {
                index = (index + 1) % n;
            }
        }
        if (index < m) {
            return false; // 好人被淘汰，不满足条件
        }
        people[index] = 0;
        count++;
    }
    return true;
}

// 寻找最小的k
int findMinK(int m) {
    int k = 1;
    while (true) {
        if (simulate(2 * m, k, m)) {
            return k;
        }
        k++;
    }
}

int main() {
    int m;
    cin >> m;
    int k = findMinK(m);
    cout << k << endl;
    return 0;
}
