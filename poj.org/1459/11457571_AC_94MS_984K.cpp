
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct edge {
    int from, to, cap, flow;
    edge(int _from, int _to, int _cap, int _flow)
        : from(_from), to(_to), cap(_cap), flow(_flow) {}
};

const int MAXN = 110;
const int INFS = 0x3fffffff;

vector<edge> edges;
vector<int> G[MAXN];
int p[MAXN], gap[MAXN], dist[MAXN], cur[MAXN];

int augment(int s, int t) {
    int x = t, aug = INFS;
    while (x != s) {
        edge& e = edges[p[x]];
        aug = min(aug, e.cap - e.flow);
        x = edges[p[x]].from;
    }
    x = t;
    while (x != s) {
        edges[p[x]].flow += aug;
        edges[p[x]^1].flow -= aug;
        x = edges[p[x]].from;
    }
    return aug;
}

int sap(int s, int t, int n) {
    int maxflow = 0;

    memset(gap, 0, sizeof(int)*(n+1));
    memset(cur, 0, sizeof(int)*(n+1));
    memset(dist, 0, sizeof(int)*(n+1));

    gap[0] = n;
    int x = s;
    while (dist[s] < n) {
        if (x == t) {
            maxflow += augment(s, t);
            x = s;
        }
        bool flag = false;
        for (int i = cur[x]; i < G[x].size(); i++) {
            edge& e = edges[G[x][i]];
            if (e.cap > e.flow && dist[x] == dist[e.to] + 1) {
                flag = true;
                p[e.to] = G[x][i];
                cur[x] = i;
                x = e.to;
                break;
            }
        }
        if (!flag) {
            int m = n - 1;
            for (int i = 0; i < G[x].size(); i++) {
                edge& e = edges[G[x][i]];
                if (e.cap > e.flow) 
                    m = min(m, dist[e.to]);
            }
            if (--gap[dist[x]] == 0)  break;
            gap[dist[x] = m+1] += 1;
            cur[x] = 0;
            if (x != s) x = edges[p[x]].from;
        }
    }
    return maxflow;
}

void addedge(int u, int v, int cap) {
    edges.push_back(edge(u, v, cap, 0));
    edges.push_back(edge(v, u, 0, 0));
    int m = edges.size();
    G[u].push_back(m - 2);
    G[v].push_back(m - 1);
}

int main() {
    int n, np, nc, m;
    while (scanf("%d", &n) != EOF) {
        scanf("%d%d%d", &np, &nc, &m);
        
        edges.clear();
        for (int i = 0; i <= n+2; i++)
            G[i].clear();

        int u, v, cap;
        for (int i = 0; i < m; i++) {
            scanf(" (%d,%d)%d ", &u, &v, &cap);
            addedge(u + 2, v + 2, cap);
        }
        for (int i = 0; i < np; i++) {
            scanf(" (%d)%d ", &v, &cap);
            addedge(1, v + 2, cap);
        }
        for (int i = 0; i < nc; i++) {
            scanf(" (%d)%d ", &u, &cap);
            addedge(u + 2, n + 2, cap);
        }
        printf("%d\n", sap(1, n + 2, n + 2));
    }
    return 0;
}