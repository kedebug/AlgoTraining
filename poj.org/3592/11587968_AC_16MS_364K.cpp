
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1610;
vector<int> G[MAXN];
vector<int> G1[MAXN];
stack<int> S;
int dfn[MAXN], low[MAXN], sccno[MAXN], sccnum, cflag;
int row, col, F[MAXN], ore[MAXN], w[MAXN];
char map[50][50];

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
    if (low[u] == dfn[u]) {
        sccnum += 1;
        int v = -1;
        while (v != u) {
            v = S.top();
            S.pop();
            sccno[v] = sccnum;
            w[sccnum] += ore[v];
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

int dp(int u) {
    if (F[u]) return F[u];
    F[u] = w[u];
    int x = 0;
    for (int i = 0; i < G1[u].size(); i++) {
        int v = G1[u][i];
        x = max(x, dp(v));
    }
    if (x) F[u] += x;
    return F[u];
}

inline int ID(int i, int j) { return i * col + j + 1; }

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        scanf("%d%d", &row, &col);

        int n = ID(row - 1, col - 1);
        for (int i = 1; i <= n; i++)
            G[i].clear(), G1[i].clear();

        for (int i = 0; i < row; i++)
            scanf("%s", map[i]);

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (map[i][j] == '#') continue;
                if (i + 1 < row && map[i+1][j] != '#')
                    G[ID(i, j)].push_back(ID(i+1, j));
                if (j + 1 < col && map[i][j+1] != '#')
                    G[ID(i, j)].push_back(ID(i, j+1));
                ore[ID(i, j)] = map[i][j] - '0';
                if (map[i][j] == '*') {
                    int x, y;
                    scanf("%d%d", &x, &y);
                    if (map[x][y] != '#')
                        G[ID(i, j)].push_back(ID(x, y));
                    ore[ID(i, j)] = 0;
                }
            }
        }
        for (int i = 0; i <= n; i++)
            F[i] = w[i] = 0;
        findscc(n);
        for (int u = 1; u <= n; u++) {
            for (int i = 0; i < G[u].size(); i++) {
                int v = G[u][i];
                if (sccno[u] != sccno[v]) 
                    G1[sccno[u]].push_back(sccno[v]);
            }
        }
        printf("%d\n", dp(sccno[ID(0, 0)]));
    }
    return 0;
}