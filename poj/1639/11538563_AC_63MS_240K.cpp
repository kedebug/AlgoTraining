#include <iostream>
#include <map>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#define MAXN 105
#define MAXM 100005
#define INF 1000000000
using namespace std;
struct node
{
    int v, w, next;
}edge[MAXM];
struct Edge
{
    int u, v, w;
    Edge(){}
    Edge(int a, int b, int c){u = a; v = b; w = c;}
    void init(){w = 0;}
    bool operator >(const Edge &a) const{
        return w > a.w;
    }
}mx[MAXN];//用于存储每个点到park点的最大边
int n, m, k, sum;//sum为结果
int e, head[MAXN], vis[MAXN], dis[MAXN], use[MAXN][MAXN];//head用于邻接表 vis是标记数组 dis用于求最小生成树
//use用来标记两点之间是否有边
int blocks, size[MAXN], belong[MAXN], nearvex[MAXN];//blocks表示去除park后有几个连通块  size是每个连通块的个数
//belong表示该点属于哪个连通块  nearvex用于在生成树中记录边
int point[MAXN], link[MAXN]; //point表示每个连通块中与park点最近的点  link则是该点与park点的距离
map<string, int>mp; //用于映射名字
void init()
{
    e = 0, n = 1;
    blocks = 0, sum = 0;
    memset(head, -1, sizeof(head));
    memset(vis, 0, sizeof(vis));
    memset(size, 0, sizeof(size));
    memset(use, 0, sizeof(use));
    for(int i = 1; i < MAXN; i++) mx[i].init();
    memset(nearvex, 0, sizeof(nearvex));
    mp.clear();
}
void insert(int x, int y, int w)
{
    edge[e].v = y;
    edge[e].w = w;
    edge[e].next = head[x];
    head[x] = e++;
}
int getId(char s[])
{
    if(mp.find(s) == mp.end()) mp[s] = ++n;
    else return mp[s];
    return n;
}
void dfs(int v) //该dfs将图分成了一些连通块
{
    vis[v] = 1;
    size[blocks]++;
    belong[v] = blocks;
    for(int i = head[v]; i != -1; i = edge[i].next)
        if(!vis[edge[i].v]) dfs(edge[i].v);
}
void prim(int cur) //对某个连通块求最小生成树
{
    for(int i = 1; i <= n; i++) dis[i] = INF;
    for(int i = 1; i <= n; i++) //设置块内某点为起点来求生成树
        if(belong[i] == cur)
        {
            dis[i] = 0;
            break;
        }
        for(int i = 1; i <= size[cur]; i++)  //循环次数为该块的顶点数，因为这与一般的求MST略微不同
        {
            int mi = INF, pos = -1;
            for(int j = 1; j <= n; j++)
                if(nearvex[j] != -1 && mi > dis[j])
                    mi = dis[j], pos = j;
            if(pos != -1)
            {
                sum += mi;
                use[pos][nearvex[pos]] = use[nearvex[pos]][pos] = 1; //标记生成树中所用的边
                nearvex[pos] = -1;
                for(int j = head[pos]; j != -1; j = edge[j].next)
                    if(nearvex[edge[j].v] != -1 && dis[edge[j].v] > edge[j].w)
                    {
                        dis[edge[j].v] = edge[j].w;
                        nearvex[edge[j].v] = pos;
                    }
            }
        }
}
void getMax(int v, int fa, int w) //该函数用于更新新的生成树中点到park点的最大边
{
    nearvex[v] = fa;
    Edge t(v, fa, w);
    if(mx[fa] > t) mx[v] = mx[fa];
    else mx[v] = t;
    for(int i = head[v]; i != -1; i = edge[i].next)
        if(use[v][edge[i].v] && edge[i].v != fa) getMax(edge[i].v, v, edge[i].w); //必须是生成树中的边并且不是回边才往下搜
}
void GetMdegreeMST()
{
    vis[1] = 1;
    for(int i = 2; i <= n; i++) //求连通块
        if(!vis[i])
        {
            blocks++;
            dfs(i);
        }
        nearvex[1] = -1;
        for(int i = 1; i <= blocks; i++) prim(i);
        for(int i = 1; i <= n; i++) link[i] = INF;
        for(int i = head[1]; i != -1; i = edge[i].next)  //生成一棵m度的生成树
            if(link[belong[edge[i].v]] > edge[i].w)
            {
                link[belong[edge[i].v]] = edge[i].w;
                point[belong[edge[i].v]] = edge[i].v;
            }
            for(int i = 1; i <= blocks; i++) //将park点与每个连通块中与其最近的点相连，并且标记边
            {
                sum += link[i];
                use[1][point[i]] = use[point[i]][1] = 1;
            }
}
void slove()
{
    int degree = blocks;
    getMax(1, 0, 0); //首先从park点出发求一遍最大边
    while(degree < k) //尝试迭代 k - degree次
    {
        int maxval = 0, pos = 0, w;
        for(int i = head[1]; i != -1; i = edge[i].next) //用于找到差值最大的点
            if(!use[1][edge[i].v] && mx[edge[i].v].w - edge[i].w > maxval)
            {
                maxval = mx[edge[i].v].w - edge[i].w, pos = edge[i].v;
                w = edge[i].w;
            }
            if(!pos) break;
            sum -= maxval;//更新答案
            degree++;
            use[mx[pos].u][mx[pos].v] = use[mx[pos].v][mx[pos].u] = 0;//将最大边删除
            use[1][pos] = use[pos][1] = 1;
            getMax(pos, 1, w);//更新最大边
    }
}
int main()
{
    char s1[55], s2[55];
    int w;
    scanf("%d", &m);
    init();
    mp["Park"] = 1;
    for(int i = 0; i < m; i++)
    {
        scanf("%s%s%d", s1, s2, &w);
        insert(getId(s1), getId(s2), w);
        insert(getId(s2), getId(s1), w);
    }
    scanf("%d", &k);
    GetMdegreeMST();
    slove();
    printf("Total miles driven: %d\n", sum);
    return 0;
}
