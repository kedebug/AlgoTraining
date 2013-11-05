
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 700;
const int INFS = 0x3FFFFFFF;

struct edge {
    int from, to, cap, flow;
    edge(int _from, int _to, int _cap, int _flow) 
        : from(_from), to(_to), cap(_cap), flow(_flow) {}
};

struct Dinic {
    vector<edge> edges;
    vector<int> G[MAXN];
    int n, s, t, d[MAXN];
    bool vis[MAXN];

    void addedge(int u, int v, int cap) {
        edges.push_back(edge(u, v, cap, 0));
        edges.push_back(edge(v, u, 0, 0));
        G[u].push_back(edges.size() - 2);
        G[v].push_back(edges.size() - 1);
    }

    bool BFS() {
        queue<int> Q;
        memset(d, 0, sizeof(d));
        memset(vis, false, sizeof(vis));
        d[s] = 0;
        vis[s] = true;
        Q.push(s);

        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            for (int i = 0; i < G[u].size(); i++) {
                edge& e = edges[G[u][i]];
                if (e.cap > e.flow && !vis[e.to]) {
                    vis[e.to] = true;
                    d[e.to] = d[u] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x, int a) {
        if (x == t || a == 0)
            return a;

        int flow = 0;
        for (int i = 0; i < G[x].size(); i++) {
            edge& e = edges[G[x][i]];
            if (d[e.to] == d[x] + 1) {
                int f = DFS(e.to, min(a, e.cap - e.flow));
                if (f < 0) continue;
                flow += f;
                e.flow += f;
                edges[G[x][i]^1].flow -= f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }

    int maxflow(int s, int t) {
        this->s = s, this->t = t;
        int flow = 0;
        while (BFS()) {
            flow += DFS(s, INFS);
        }
        return flow;
    }

    void clearall(int n) {
        this->n = n;
        edges.clear();
        for (int i = 0; i < n; i++) 
            G[i].clear();
    }
};

Dinic dinic;
const int MAXT = 30;
int n, w[MAXT], d[MAXT], a[MAXT][MAXT];


inline int ID(int u) { return n*n + u + 1; }
inline int ID(int u, int v) { return u*n + v + 1; }

bool canwin(int team) {
    int total = w[team], full = 0;
    for (int i = 0; i < n; i++)
        total += a[team][i];
    for (int i = 0; i < n; i++)
        if (w[i] > total) return false;

    int s = 0, t = n*n + n + 1;
    dinic.clearall(n*n + n + 2);
    for (int u = 0; u < n; u++) {
        for (int v = u+1; v < n; v++) {
            full += a[u][v];
            if (a[u][v] > 0)
                dinic.addedge(s, ID(u, v), a[u][v]);
            dinic.addedge(ID(u, v), ID(u), INFS);
            dinic.addedge(ID(u, v), ID(v), INFS);
        }
        if (total > w[u])
            dinic.addedge(ID(u), t, total - w[u]);
    }
    int flow = dinic.maxflow(s, t);
    return flow == full;
}

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d%d", &w[i], &d[i]);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &a[i][j]);
        vector<int> ans;
        ans.clear();
        for (int i = 0; i < n; i++) {
            if (canwin(i)) ans.push_back(i+1); 
        }
        for (int i = 0; i < ans.size(); i++) {
            if (i == 0) printf("%d", ans[i]);
            else printf(" %d", ans[i]);
        }
        printf("\n");
    }
    return 0;
}