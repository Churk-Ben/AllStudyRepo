#include <iostream>

using namespace std;

// 数据结构定义
struct Elem
{
    int key;
    int t;
    int flag;
};

struct HashList
{
    Elem *base;
    int length;
};

// 插入数列
const int DATA[] = {23, 5, 17, 12, 26, 31, 13, 4, 6};
const int DATA_SIZE = sizeof(DATA) / sizeof(DATA[0]);
const int HASH_SIZE = 13;

// 函数声明
void InitHashList(HashList &HL);
void CreateHashList(HashList &HL);
void PrintHashList(HashList HL);
void IndexHashList(HashList HL);
void CalcuASL(HashList HL);

// 初始化哈希表
void InitHashList(HashList &HL)
{
    HL.length = HASH_SIZE;
    HL.base = new Elem[HL.length];
    for (int i = 0; i < HL.length; ++i)
    {
        HL.base[i].key = 0;
        HL.base[i].t = 0;
        HL.base[i].flag = 0; // 0 表示空
    }
}

// 建立哈希表
void CreateHashList(HashList &HL)
{
    // 遍历输入数据
    for (int i = 0; i < DATA_SIZE; ++i)
    {
        int key = DATA[i];
        int hashVal = key % 13;
        int index = hashVal;
        int conflicts = 1;

        while (HL.base[index].flag == 1)
        {
            conflicts++;
            index = (index + 1) % HL.length;
            if (conflicts > HL.length)
            {
                return;
            }
        }

        // 插入数据
        HL.base[index].key = key;
        HL.base[index].flag = 1;
        HL.base[index].t = conflicts;
    }
}

// 显示哈希表
void PrintHashList(HashList HL)
{
    for (int i = 0; i < HL.length; ++i)
    {
        if (HL.base[i].flag == 1)
        {
            cout << i << "\t" << HL.base[i].key << "\t" << HL.base[i].t << endl;
        }
    }
}

// 计算平均查找长度 ASL
void CalcuASL(HashList HL)
{
    float totalTimes = 0;
    int count = 0;
    for (int i = 0; i < HL.length; ++i)
    {
        if (HL.base[i].flag == 1)
        {
            totalTimes += HL.base[i].t;
            count++;
        }
    }

    if (count > 0)
    {
        cout << "平均次数: " << totalTimes / count << endl;
    }
    return;
}

// 查找
void IndexHashList(HashList HL)
{
    int key;
    cin >> key;

    int hashVal = key % 13;
    int index = hashVal;
    int compareCount = 1;
    bool found = false;

    for (int i = 0; i < HL.length; ++i)
    {
        if (HL.base[index].flag == 0)
        {
            break;
        }

        if (HL.base[index].key == key)
        {
            found = true;
            cout << index << "\t" << compareCount << endl;
            break;
        }

        index = (index + 1) % HL.length;
        compareCount++;
    }

    if (!found)
    {
        cout << "无记录." << endl;
    }
}

int main()
{
    HashList H;
    InitHashList(H);
    CreateHashList(H);

    int choice;
    while (true)
    {
        cout << "\n========================" << endl;
        cout << "1. 显示哈希表" << endl;
        cout << "2. 查找" << endl;
        cout << "3. 计算平均查找长度 ASL" << endl;
        cout << "4. 退出" << endl;
        cout << ">>>";

        if (!(cin >> choice))
        {
            // 处理非数字输入
            cin.clear();
            while (cin.get() != '\n')
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            PrintHashList(H);
            break;
        case 2:
            IndexHashList(H);
            break;
        case 3:
            CalcuASL(H);
            break;
        case 4:
            delete[] H.base;
            return 0;
        default:
            cout << "无效选择." << endl;
        }
    }
    return 0;
}
