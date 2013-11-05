
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1010;
vector<int> G[MAXN];
stack<int> S;
vector<int> G0[MAXN];
int dfn[MAXN], low[MAXN], sccno[MAXN], sccnum, cflag;
int indeg[MAXN];

void tarjan(int u) {
    dfn[u] = low[u] = ++cflag;
    S.push(u);

    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (!sccno[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        sccnum += 1;
        int v = -1;
        while (v != u) {
            v = S.top();
            S.pop();
            sccno[v] = sccnum;
        }
    }
}

void findscc(int n) {
    for (int i = 0; i <= n; i++)
        dfn[i] = low[i] = sccno[i] = 0;
    sccnum = cflag = 0;
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
}

bool topsort(int n) {
    stack<int> s;
    
    for (int i = 1; i <= n; i++) {
        if (!indeg[i]) s.push(i);
        if (s.size() == 2) return false;
    }
    while (!s.empty()) {
        int u = s.top();
        s.pop();
        bool flag = false;
        for (int i = 0; i < G0[u].size(); i++) {
            int v = G0[u][i];
            indeg[v] -= 1;
            if (!indeg[v]) {
                if (flag) return false;
                s.push(v);
                flag = true;
            }
        }
    }
    return true;
}

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i <= n; i++)
            G[i].clear();
        while (m--) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
        }
        findscc(n);
        for (int i = 0; i <= sccnum; i++)
            G0[i].clear(), indeg[i] = 0;
        for (int u = 1; u <= n; u++) {
            for (int i = 0; i < G[u].size(); i++) {
                int v = G[u][i];
                if (sccno[u] != sccno[v]) {
                    indeg[sccno[v]] += 1;
                    G0[sccno[u]].push_back(sccno[v]);
                }
            }
        }
        if (topsort(sccnum))
            printf("Yes\n");
        else 
            printf("No\n");
    }
    return 0;
}