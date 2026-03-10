#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cstdlib>
#include <ctime>

// 模板函数声明
template <typename T>
void output(const T &c);

int generate_random_number();
void test1();
void test2();

int main()
{
    std::srand(std::time(0));
    std::cout << "测试1: \n";
    test1();
    std::cout << "\n测试2: \n";
    test2();
}

// 输出容器对象c中的元素
template <typename T>
void output(const T &c)
{
    for (auto &i : c)
        std::cout << i << ' ';
    std::cout << '\n';
}

// 返回[0, 100]区间内的一个随机整数
int generate_random_number()
{
    return std::rand() % 101;
}

// 测试1：对容器类对象指定迭代器区间赋值、排序
void test1()
{
    using namespace std;
    // 创建一个动态数组对象v0, 对象大小为10
    vector<int> v0(10);
    generate(v0.begin(), v0.end(), generate_random_number); // 生成随机数填充v0
    cout << "v0: ";
    output(v0);
    vector<int> v1{v0};
    sort(v1.begin(), v1.end()); // 对整个vector排序
    cout << "v1: ";
    output(v1);
    vector<int> v2{v0};
    sort(v2.begin() + 1, v2.end() - 1); // 只对中间部分排序，不包含首尾元素
    cout << "v2: ";
    output(v2);
}

// 测试2：对容器类对象指定迭代器区间赋值、计算最大值/最小值/均值
void test2()
{
    using namespace std;
    vector<int> v0(10);
    generate(v0.begin(), v0.end(), generate_random_number);
    cout << "v0: ";
    output(v0);
    // 求最大值和最小值
    auto min_iter = min_element(v0.begin(), v0.end());
    auto max_iter = max_element(v0.begin(), v0.end());
    cout << "最小值: " << *min_iter << endl;
    cout << "最大值: " << *max_iter << endl;
    // 同时求最大值和最小值
    auto ans = minmax_element(v0.begin(), v0.end());
    cout << "最小值: " << *(ans.first) << endl;
    cout << "最大值: " << *(ans.second) << endl;
    // 求平均值
    double avg1 = accumulate(v0.begin(), v0.end(), 0.0) / v0.size();
    cout << "均值: " << fixed << setprecision(2) << avg1 << endl;
    sort(v0.begin(), v0.end());
    double avg2 = accumulate(v0.begin() + 1, v0.end() - 1, 0.0) / (v0.size() - 2);
    cout << "去掉最大值、最小值之后，均值: " << avg2 << endl;
}
