// 现代C++标准库、算法库体验
// 本例用到以下内容:
// 1. 字符串string, 动态数组容器类vector、迭代器
// 2. 算法库：反转元素次序、旋转元素
// 3. 函数模板、const引用作为形参

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// 模板函数声明
template <typename T>
void output(const T &c);

void test1();
void test2();
void test3();

int main()
{
    std::cout << "测试1: \n";
    test1();
    std::cout << "\n测试2: \n";
    test2();
    std::cout << "\n测试3: \n";
    test3();
}

// 输出容器对象c中的元素
template <typename T>
void output(const T &c)
{
    for (auto &i : c)
        std::cout << i << ' ';
    std::cout << '\n';
}

// 测试1：组合使用算法库、迭代器、string反转字符串
void test1()
{
    using namespace std;
    string s0{"0123456789"};
    cout << "s0 = " << s0 << endl;
    string s1(s0);
    // 反转s1自身
    reverse(s1.begin(), s1.end());
    cout << "s1 = " << s1 << endl;
    string s2(s0.size(), ' ');
    // 将s0反转后结果拷贝到s2, s0自身不变
    reverse_copy(s0.begin(), s0.end(), s2.begin());
    cout << "s2 = " << s2 << endl;
}

// 测试2：组合使用算法库、迭代器、vector反转动态数组对象vector内数据
void test2()
{
    using namespace std;
    vector<int> v0{2, 0, 4, 9};
    cout << "v0: ";
    output(v0);
    vector<int> v1{v0};
    reverse(v1.begin(), v1.end());
    cout << "v1: ";
    output(v1);
    vector<int> v2{v0};
    reverse_copy(v0.begin(), v0.end(), v2.begin());
    cout << "v2: ";
    output(v2);
}

// 测试3：组合使用算法库、迭代器、vector实现元素旋转移位
void test3()
{
    using namespace std;
    vector<int> v0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << "v0: ";
    output(v0);
    vector<int> v1{v0};
    // 将[v1.begin(), v1.end())区间内元素循环左移1位
    rotate(v1.begin(), v1.begin() + 1, v1.end());
    cout << "v1: ";
    output(v1);
    vector<int> v2{v0};
    // 将[v1.begin(), v1.end())区间内元素循环左移2位
    rotate(v2.begin(), v2.begin() + 2, v2.end());
    cout << "v2: ";
    output(v2);
    vector<int> v3{v0};
    // 将[v1.begin(), v1.end())区间内元素循环右移1位
    rotate(v3.begin(), v3.end() - 1, v3.end());
    cout << "v3: ";
    output(v3);
    vector<int> v4{v0};
    // 将[v1.begin(), v1.end())区间内元素循环右移2位
    rotate(v4.begin(), v4.end() - 2, v4.end());
    cout << "v4: ";
    output(v4);
}
