
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 5010;
vector<int> G[MAXN];
int low[MAXN], deg[MAXN], cflag;
bool vis[MAXN];

void BCC(int u, int f) {
    low[u] = ++cflag;
    vis[u] = true;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (v == f) continue;
        if (!vis[v]) BCC(v, u);
        low[u] = min(low[u], low[v]);
    }
}

bool judge(int u, int v) {
    for (int i = 0; i < G[u].size(); i++)
        if (G[u][i] == v) return false;
    return true;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++) {
        G[i].clear();
        vis[i] = false;
        low[i] = deg[i] = 0;
    }
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (judge(u, v)) {
            G[u].push_back(v);
            G[v].push_back(u);
        }
    }
    BCC(1, 0);
    for (int u = 1; u <= n; u++) {
        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            if (low[u] != low[v])
                deg[low[u]] += 1;
        }
    }
    int leaf = 0;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1) leaf += 1;
    printf("%d\n", (leaf+1)/2);
    return 0;
}