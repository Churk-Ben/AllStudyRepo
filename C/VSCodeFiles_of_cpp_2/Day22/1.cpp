#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 分区函数：将数组分为两部分，左边小于基准，右边大于基准
int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high]; // 选择最后一个元素作为基准
    int i = (low - 1);     // 较小元素的索引

    for (int j = low; j <= high - 1; j++)
    {
        // 如果当前元素小于或等于基准
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// 快速排序主函数
void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        // pi 是分区索引
        int pi = partition(arr, low, high);

        // 分别对分区前后的子数组进行递归排序
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    vector<int> arr;
    int n;
    cout << "请输入数组元素的数量: ";
    cin >> n;
    cout << "请输入数组元素: ";
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        arr.push_back(x);
    }

    cout << "原始数组: ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;

    quickSort(arr, 0, arr.size() - 1);

    cout << "排序后数组: ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;

    return 0;
}
