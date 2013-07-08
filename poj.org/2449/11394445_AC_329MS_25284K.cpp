#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

#define MAXM 100010
#define MAXN 1010
#define INF 0x3f3f3f3f

struct Edge
{
    int v, g, f;
    int next;
    bool operator < (const Edge &a) const    //结构体重载，如果在外面重载会MLE 
    {
        if(a.f == f) return a.g < g;    //f = h + g, 此时h为t->s的最短路径。 
        else return a.f < f;
    }
}edge[MAXM], edge2[MAXM];

/*bool operator < (const node a, const node b)   //这样重载会MLE，不知为啥
{
    if(a.f == b.f) return a.g < b.g;
    else return a.f < b.f;
}*/  

int n, m, cnt;
int first[MAXN], first2[MAXN];
int d[MAXN], ct[MAXN];

void init()
{
    cnt = 0;
    memset(first, -1, sizeof(first));
    memset(first2, -1, sizeof(first2));
    memset(ct, 0, sizeof(ct));
}

void read_graph(int u, int v, int w)
{
    edge[cnt].v = v, edge[cnt].g = w;
    edge[cnt].next = first[u], first[u] = cnt;
    edge2[cnt].v = u, edge2[cnt].g = w;
    edge2[cnt].next = first2[v], first2[v] = cnt++;
} //建立正、反向图。 

void spfa(int src)
{
    queue<int> q;
    bool inq[MAXN] = {0};
    for(int i = 1; i <= n; i++) d[i] = (i == src)?0:INF;
    q.push(src);
    while(!q.empty())
    {
        int x = q.front(); q.pop();
        inq[x] = 0, ct[x]++;
        for(int e = first2[x]; e != -1; e = edge2[e].next)
        {
            int v = edge2[e].v, w = edge2[e].g;
            if(d[v] > d[x] + w)
            {
                d[v] = d[x] + w;
                if(!inq[v])
                {
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}

int A_STAR(int s, int t, int k)
{
    int tot = 0;  
    struct Edge cur, now;  
    priority_queue<Edge> Q;  
    if (s == t) k++;  
    if (d[s] == INF) return -1; //没有路径可达 
    cur.v = s, cur.g = 0, cur.f = d[s];
    Q.push(cur);  
    while(!Q.empty())
    {
        cur = Q.top(); Q.pop();
        if(cur.v == t)
        {
            tot++;  
            if(tot == k) return cur.g;  
        } 
        for(int e = first[cur.v]; e != -1; e = edge[e].next)
        {
            int v = edge[e].v, g = edge[e].g; 
            now.v = v, now.g = cur.g + g;  
            now.f = now.g + d[v];    //更新g
            Q.push(now);  
        }
    }
    return -1;  
}

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        init();
        while(m--)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            read_graph(u, v, w);
        }
        int s, e, k;
        scanf("%d%d%d", &s, &e, &k);
        spfa(e);
        int ans = A_STAR(s, e, k);
        printf("%d\n", ans);
    }
    return 0;
}