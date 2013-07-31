
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 110;

struct node {
    int dist, to;    
    node(int to_, int dist_) : to(to_), dist(dist_) {}
};

struct qnode {
    int dist, from;
    qnode(int from_, int dist_) : from(from_), dist(dist_) {}
    friend bool operator < (const qnode& lhs, const qnode& rhs) { 
        return lhs.dist > rhs.dist;
    }
};

vector<node> G[MAXN];
int M, N, price[MAXN], level[MAXN];
bool hasLimits[MAXN];

int dijkstra(int s) {
    bool visited[MAXN];
    int d[MAXN];
    memset(visited, false, sizeof(visited));
    memset(d, 0x3f, sizeof(d));

    priority_queue<qnode> Q;
    Q.push(qnode(s, 0));
    d[s] = 0;

    while (!Q.empty()) {
        int u = Q.top().from;
        Q.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i].to;
            int vd = G[u][i].dist;
            if (!hasLimits[v] && !visited[v] && d[v] > d[u] + vd) {
                d[v] = d[u] + vd;
                if (!visited[v])
                    Q.push(qnode(v, d[v]));
            } 
        }
    }
    int mincost = INT_MAX;
    for (int i = 1; i <= N; i++) {
        d[i] += price[i];
        mincost = min(mincost, d[i]);
    }
    return mincost;
}

int main() {
    scanf("%d%d", &M, &N);
    for (int i = 1; i <= N; i++) {
        int x;
        scanf("%d%d%d", &price[i], &level[i], &x);
        while (x--) {
            int v, p;
            scanf("%d%d", &v, &p);
            G[i].push_back(node(v, p));
        }
    }
    int mincost = INT_MAX;
    for (int i = 0; i <= M; i++) {
        memset(hasLimits, true, sizeof(hasLimits));
        for (int j = 1; j <= N; j++) {
            int upper = level[1] + i;
            int lower = level[1] - (M  - i);
            if (lower <= level[j] && level[j] <= upper)
                hasLimits[j] = false;
        }
        int cost = dijkstra(1);
        mincost = min(mincost, cost);
    }
    printf("%d\n", mincost);
    return 0;
}