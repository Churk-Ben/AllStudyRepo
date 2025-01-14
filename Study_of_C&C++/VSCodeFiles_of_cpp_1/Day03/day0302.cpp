#include <iostream>
using namespace std;

int X[4] = {1, 0, -1, 0};
int Y[4] = {0, 1, 0, -1};
bool visited[7][10]; // 修改为 [7][10] 以适配 ch 数组
int ch[7][10] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 1, 1, 0, 1, 0},
    {0, 0, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void dfs(int x, int y, int endx, int endy)
{
    if (x < 0 || x >= 7 || y < 0 || y >= 10)
        return; // 边界检查
    if (x == endx && y == endy)
    {
        cout << "can";
        return;
    }

    if (visited[x][y] || ch[x][y] == 1)
        return; // 先检查是否已访问或不可通过

    visited[x][y] = true; // 标记当前位置为已访问

    for (int k = 0; k < 4; k++)
    {
        dfs(x + X[k], y + Y[k], endx, endy);
    }

    visited[x][y] = false; // 回溯标记
}

int main()
{
    for (int i = 0; i < 7; i++) // 修改为 [7][10] 以适配 ch 数组
        for (int j = 0; j < 10; j++)
            visited[i][j] = false;

    dfs(2, 3, 5, 8);         // 确保目标位置在有效范围内
    cout << " cannot reach"; // 如果找不到路径也输出
}
