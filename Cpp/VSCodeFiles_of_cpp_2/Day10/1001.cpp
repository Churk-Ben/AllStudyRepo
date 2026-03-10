#include <iostream>
#include <vector>
#include <cstring>
#include <string>
using namespace std;

vector<int> filter(vector<vector<string>> tags, string target)
{
    vector<int> res;
    for (int i = 0; i < (int)tags.size(); i++)
    {
        for (int j = 0; j < (int)tags[i].size(); j++)
        {
            if (tags[i][j] == target)
            {
                res.push_back(i);
            }
        }
    }
    return res;
}

int main()
{
    vector<vector<string>> vec;
    vec = {
        {"1", "world", "冒险"},              // 0
        {"1", "卡牌", "七圣召唤", "二次元"}, // 1
        {"二次元", "动作", "world"}          // 2
    };
    vector<int> res;
    string target;
    cin >> target;
    res = filter(vec, target);
    for (int i = 0; i < (int)res.size(); ++i)
    {
        cout << res[i] << endl;
    }
    return 0;
}