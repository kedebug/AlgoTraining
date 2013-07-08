
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 1010;
const int INFS = 0x3fffffff;

struct ST {
    int v, cost, f;
    ST(int _v, int _cost, int _f) : v(_v), cost(_cost), f(_f) {}
    bool operator < (const ST& other) const { return f > other.f; }
};

struct edge {
    int v, cost;
    edge(int _v, int _cost) : v(_v), cost(_cost) {}
};

int N, M, S, T, K, dis[MAXN];

vector<edge> G[MAXN];
vector<edge> GREV[MAXN];

void spfa(int s) {
    bool vis[MAXN];
    for (int i = 1; i <= N; i++)
        dis[i] = INFS, vis[i] = false;

    dis[s] = 0;
    vis[s] = true;
    queue<int> Q;
    Q.push(s);

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        for (int i = 0; i < GREV[u].size(); i++) {
            int v = GREV[u][i].v;
            int cost = GREV[u][i].cost;
            if (dis[v] > dis[u] + cost) {
                dis[v] = dis[u] + cost;
                if (!vis[v]) {
                    vis[v] = true; Q.push(v);
                }
            }
        }
        vis[u] = false;
    }
}

// 335 
int bfs(int s, int t, int k) {
    if (dis[s] == INFS)
        return -1;

    if (s == t) 
        k += 1;

    priority_queue<ST> Q;
    Q.push(ST(s, 0, dis[s]));

    int count[MAXN];
    memset(count, 0, sizeof(count));

    while (!Q.empty()) {
        ST u = Q.top();
        Q.pop();

        count[u.v] += 1;
        if (count[t] == k)
            return u.cost;
        if (count[u.v] > k)
            continue;

        for (int i = 0; i < G[u.v].size(); i++)
            Q.push(ST(G[u.v][i].v, u.cost + G[u.v][i].cost, u.cost + G[u.v][i].cost + dis[G[u.v][i].v]));
    }
    return -1;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back(edge(v, w));
        GREV[v].push_back(edge(u, w));
    }
    scanf("%d%d%d", &S, &T, &K);
    spfa(T);
    printf("%d\n", bfs(S, T, K));
    return 0;
}