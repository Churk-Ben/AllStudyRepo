#include <iostream>
#include <windows.h>

#define MAXVEX 100
using namespace std;

typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *next;
} ArcNode;

typedef struct VNode
{
    char data;
    ArcNode *first;
} VNode, AdjList[MAXVEX];

typedef struct
{
    AdjList vertices;
    int vexnum, arcnum;
} Graph;

int Locate(Graph G, char a)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data == a)
        {
            return i;
        }
    }
    return -1;
}

void CreateDG(Graph &G)
{
    int k;
    char v1, v2;
    ArcNode *p;
    cout << "vertices and arcs: ";
    cin >> G.vexnum >> G.arcnum;
    cout << "data:";
    for (int i = 0; i < G.vexnum; i++)
    {
        cin >> G.vertices[i].data;
        G.vertices[i].first = nullptr;
    }
    cout << "arcs:" << endl;
    for (k = 0; k < G.arcnum; k++)
    {
        cin >> v1 >> v2;
        int i = Locate(G, v1);
        int j = Locate(G, v2);
        p = new ArcNode;
        p->adjvex = j;
        p->next = G.vertices[i].first;
        G.vertices[i].first = p;
    }
}

void DFS(Graph G, int v, bool visited[])
{
    visited[v] = true;
    cout << G.vertices[v].data << " ";
    ArcNode *p = G.vertices[v].first;
    while (p)
    {
        int w = p->adjvex;
        if (!visited[w])
        {
            DFS(G, w, visited);
        }
        p = p->next;
    }
}

void DFSTraverse(Graph G, int start)
{
    bool visited[MAXVEX] = {false};
    DFS(G, start, visited);
    for (int v = 0; v < G.vexnum; v++)
    {
        if (!visited[v])
        {
            DFS(G, v, visited);
        }
    }
}

void BFS(Graph G, int v, bool visited[])
{
    int queue[MAXVEX], front = 0, rear = 0;
    visited[v] = true;
    cout << G.vertices[v].data << " ";
    queue[rear++] = v;
    while (front < rear)
    {
        int u = queue[front++];
        ArcNode *p = G.vertices[u].first;
        while (p)
        {
            int w = p->adjvex;
            if (!visited[w])
            {
                visited[w] = true;
                cout << G.vertices[w].data << " ";
                queue[rear++] = w;
            }
            p = p->next;
        }
    }
}

void BFSTraverse(Graph G, int start)
{
    bool visited[MAXVEX] = {false};
    BFS(G, start, visited);
    for (int v = 0; v < G.vexnum; v++)
    {
        if (!visited[v])
        {
            BFS(G, v, visited);
        }
    }
}

int main()
{
    SetConsoleCP(65001);
    Graph G;
    char c;
    cout << "start vertex: ";
    cin >> c;
    CreateDG(G);
    int start = Locate(G, c);
    cout << "DFS Traversal: " << endl;
    DFSTraverse(G, start);
    cout << endl;
    cout << "BFS Traversal: " << endl;
    BFSTraverse(G, start);
    return 0;
}
