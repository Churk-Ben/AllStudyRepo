#include<iostream>
using namespace std;
int X[4]={1,0,-1,0};
int Y[4]={0,1,0,-1};
bool visited[10][10];
int ch[7][10]={
    {0,0,0,0,0,0,0,0,0},
    {0,1,1,0,1,1,0,1,0},
    {0,0,1,0,1,0,1,1,1},
    {1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
};
void dfs(int x,int y,int endx,int endy)
{
    if(x==endx&&y==endy)
    {
        cout<<"can";
        return;
    }
    for(int k=0;k<4;k++)
    {
        if(!visited[x][y]&&ch[x][y]==0)
        {
            visited[x][y]=true;
            dfs(x+X[k],y+Y[k],endx,endy);
        }
    }
}
int main()
{
    for(int i=0;i<100;i++)
        for(int j=0;j<100;j++)
            visited[i][j]=false;
    dfs(2,3,9,5);
}