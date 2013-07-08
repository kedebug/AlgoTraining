#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
using namespace std;

const int V = 21;
const int INF = 1 << 30;
int n;

struct Edge
{
    int from;
    int to;
    int weight;
};

map<string,int> Map;
int graph[V][V];
Edge edges[V];
int vertexNum;
int s;
bool visited[V];//边(0,i)是否在edges中

void init()
{
    memset(visited,0,sizeof(visited));
    Map.clear();
    for(int i = 0; i < V; ++i)
    {
        for(int j = 0; j < V; ++j)
        {
            graph[i][j] = INF;
        }
    }
}


void input()
{
    string name1,name2;
    int dis;
    Map["Park"] = 0;
    int k = 1;
    for(int i = 0; i < n; ++i)
    {
        cin >> name1 >> name2 >> dis;
        if(Map.find(name1) == Map.end())
            Map[name1] = k++;
        if(Map.find(name2) == Map.end())
            Map[name2] = k++;
        int id1 = Map[name1];
        int id2 = Map[name2];
        graph[id1][id2] = graph[id2][id1] = dis;
    }
    scanf("%d",&s);
}

//求v0 - v(_vertexNum-1)的最小生成树
int Prim(int _vertexNum)
{
    int mstWeight = 0;
    for(int i = 1; i < _vertexNum - 1; ++i)
    {
        edges[i].from = 1;
        edges[i].to = i + 1;
        edges[i].weight = graph[1][i+1];
    }
    for (int i = 2; i < _vertexNum; ++i)
    {
        int id = i-1;
        int minW = edges[i-1].weight;
        for (int j = i; j < _vertexNum-1; ++j)
        {
            if (minW > edges[j].weight)
            {
                minW = edges[j].weight;
                id = j;
            }
        }
        mstWeight += minW;

        swap(edges[i-1],edges[id]); 
        int k = edges[i-1].to;

        for (int j = i; j < _vertexNum -1; ++j)
        {
            int v = edges[j].to;
            int w = graph[k][v];
            if(w < edges[j].weight)
            {
                edges[j].weight = w;
                edges[j].from = k;
            }
        }
    }
    return mstWeight;
}

//返回回路中最大的边
bool isCycle;
void maxWeightInCycle(int _mv,int _from,int _to,int& _maxW,int& _id)
{
    if (_to == _mv)
    {
        isCycle = true;
        return;
    }
    for (int i = 0; i < vertexNum-1; ++i)
    {
        if (edges[i].from != _to && edges[i].to != _to)
        {
            continue;
        }
        if (edges[i].from == _to && edges[i].to != _from)
        {
            maxWeightInCycle(_mv,_to,edges[i].to,_maxW,_id);
            if (isCycle)
            {
                if (_maxW < edges[i].weight && edges[i].to != 0)
                {
                    _maxW = edges[i].weight;
                    _id = i;
                }
                break;
            }
        }
        else if(edges[i].to == _to && edges[i].from != _from)
        {
            maxWeightInCycle(_mv,_to,edges[i].from,_maxW,_id);
            if (isCycle)
            {
                if (_maxW < edges[i].weight && edges[i].from != 0)
                {
                    _maxW = edges[i].weight;
                    _id = i;
                }
                break;
            }
        }
    }
}

void Test()
{
    init();
    input();
    vertexNum = Map.size();
    
    int ans = Prim(vertexNum);//v0 - vn-1
    int minW = INF; 
    int id = -1;
    for (int i = 1; i < vertexNum; ++i)
    {
        if (minW > graph[0][i])
        {
            minW = graph[0][i];
            id = i;
        }
    }
    ans += graph[0][id];
    visited[id] = true;
    //添加边(0,id)
    edges[0].from = 0;
    edges[0].to = id;
    edges[0].weight = minW;

    //枚举顶点0 的度
    for (int d = 2; d <= s; ++d)
    {
        int dec = INF;
        int edgeId = -1;
        id = -1;
        for (int i = 1; i < vertexNum; ++i)
        {
            if (visited[i])//已经在MST树中了
            {
                continue;
            }
            int maxW = 0,maxId = -1;
            isCycle = false;
            //添加边(0-i)，并返回回路最大边
            maxWeightInCycle(0,0,i,maxW,maxId);
            if (dec > graph[0][i] - maxW)
            {
                dec = graph[0][i] - maxW;
                edgeId = maxId;
                id = i;
            }
        }
        if (dec >= 0)
        {
            break;
        }
        else
        {
            //将回路最大边删除，并修改为0点的边
            if (edgeId != -1)
            {
                edges[edgeId].from = 0;
                edges[edgeId].to = id;
                edges[edgeId].weight = graph[0][id];
            }
            visited[id] = true;
            ans += dec;
        }
    }
    printf("Total miles driven: %d\n",ans);
}

int main()
{
    //freopen("data.txt","r",stdin);
    while(scanf("%d",&n) != EOF)
    {
        Test();
    }
    return 0;
}