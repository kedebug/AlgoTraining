
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int MAXN = 100010;
const int INFS = 0x7FFFFFFF;

vector<int> G[MAXN];
int F[MAXN], val[MAXN], indeg[MAXN];

int dp(int u) {
    if (F[u] != -INFS) 
        return F[u];

    F[u] = val[u];
    int ans = -INFS;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        ans = max(ans, dp(v));
    }
    if (ans != -INFS)
        F[u] += ans;
    return F[u];
}

int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
            G[i].clear();
            F[i] = -INFS, indeg[i] = 0;
        }
        while (m--) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[v].push_back(u);
            indeg[u] += 1;
        }
        int ans = -INFS;
        for (int i = 1; i <= n; i++)
            if (!indeg[i]) 
                ans = max(ans, dp(i));
        printf("%d\n", ans);
    }
    return 0;
}