#include<iostream>
#include<stdio.h>
#include<string.h>
#include<queue>
#include<vector>
using namespace std;
const int N = 1011;
const int inf = 0x7ffffff;
int n, m, s, t, k, dis[N];
struct node {
    int v, l;
    node(int v, int l) : v(v), l(l) {
    }
    inline bool operator<(const node & b) const {
        return l + dis[v] > b.l + dis[b.v]; //这里是对估价函数的使用，使得路径最短的先出队
    }
};
vector<node> p[N]; /* 图的邻接表表示（反图） */
vector<node> g[N]; /* 正图 */
int getint() //这个getchar的输入对大数据量输入非常有用，甚至可以挽救效率不高的算法
{
    int ret = 0;
    char tmp;
    while (!isdigit(tmp = getchar()));
    do {
        ret = (ret << 3)+(ret << 1) + tmp - '0';
    } while (isdigit(tmp = getchar()));
    return ret;
}
void dijkstra() //求所有点到终点的最短路径
{
    int i, u, mark[N];
    for (i = 1; i <= N; i++)dis[i] = inf;
    memset(mark, 0, sizeof mark);
    priority_queue<node> heap;
    dis[t] = 0;
    heap.push(node(t, 0));
    while (!heap.empty()) {
        u = heap.top().v;
        heap.pop();
        if (mark[u])continue;
        mark[u] = 1;
        for (i = 0; i < p[u].size(); i++)
            if (!mark[p[u][i].v] && dis[u] + p[u][i].l < dis[p[u][i].v]) {
                dis[p[u][i].v] = dis[u] + p[u][i].l;
                heap.push(node(p[u][i].v, dis[p[u][i].v]));
            }
    }
}
int A_star() //A*搜索
{
    int u, i, len, c[N];
    if (dis[s] == inf)return -1;
    priority_queue<node> heap;
    memset(c, 0, sizeof c);
    heap.push(node(s, 0));
    while (!heap.empty()) {
        u = heap.top().v;
        len = heap.top().l;
        heap.pop();
        c[u]++;
        if (c[t] == k)return len;
        if (c[u] > k)continue;
        for (i = 0; i < g[u].size(); i++)
            heap.push(node(g[u][i].v, len + g[u][i].l));
    }
    return -1;
}
int main() {

 
    int i, u, v, w;
    while (scanf("%d %d", &n, &m) != EOF) {
        for (i = 0; i < m; i++) {
            /*u = getint();
            v = getint();
            w = getint();*/
            scanf ("%d %d %d", &u, &v, &w);
           // printf ("%d %d %d\n", u, v, w);
            g[u].push_back(node(v, w));
            p[v].push_back(node(u, w));
        }
        /*s = getint();
        t = getint();
        k = getint();*/
        scanf ("%d %d %d", &s, &t, &k);
        if (s == t) k++;  /* 如果 s==t ，那么就是求 k+1 短路 */
        dijkstra();
        printf("%d\n", A_star());
    }
    return 0;
}