#include <iostream>
using namespace std;

int X[4] = {1, 0, -1, 0};
int Y[4] = {0, 1, 0, -1};
bool visited[7][10]; // �޸�Ϊ [7][10] ������ ch ����
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
        return; // �߽���
    if (x == endx && y == endy)
    {
        cout << "can";
        return;
    }

    if (visited[x][y] || ch[x][y] == 1)
        return; // �ȼ���Ƿ��ѷ��ʻ򲻿�ͨ��

    visited[x][y] = true; // ��ǵ�ǰλ��Ϊ�ѷ���

    for (int k = 0; k < 4; k++)
    {
        dfs(x + X[k], y + Y[k], endx, endy);
    }

    visited[x][y] = false; // ���ݱ��
}

int main()
{
    for (int i = 0; i < 7; i++) // �޸�Ϊ [7][10] ������ ch ����
        for (int j = 0; j < 10; j++)
            visited[i][j] = false;

    dfs(2, 3, 5, 8);         // ȷ��Ŀ��λ������Ч��Χ��
    cout << " cannot reach"; // ����Ҳ���·��Ҳ���
}
