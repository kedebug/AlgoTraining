#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 1010;
const int MAXM = 110;
const int INFS = 0x3fffffff;

struct ST {
    int u, fuel, cost;
    ST(int _u, int _fuel, int _cost) : u(_u), fuel(_fuel), cost(_cost) {}
    bool operator < (const ST& other) const { return cost > other.cost; }
};

struct edge {
    int v, d;
    edge* next;
} *V[MAXN], ES[MAXN*10*2];

int EC, price[MAXN], dp[MAXN][MAXM];
bool vis[MAXN][MAXM];

void addedge(int u, int v, int d) {
    ES[++EC].next = V[u];
    V[u] = ES + EC;
    V[u]->v = v; V[u]->d = d;
}

int bfs(int s, int t, int vol) {
    priority_queue<ST> Q;
    Q.push(ST(s, 0, 0));
    dp[s][0] = 0;

    while (!Q.empty()) {
        int u = Q.top().u;
        int fuel = Q.top().fuel;
        int cost = Q.top().cost;
        Q.pop();

        vis[u][fuel] = true;

        if (u == t)
            return cost;

        if (fuel + 1 <= vol && !vis[u][fuel+1] &&
            dp[u][fuel+1] > dp[u][fuel] + price[u]) {
                dp[u][fuel+1] = dp[u][fuel] + price[u];
                Q.push(ST(u, fuel+1, dp[u][fuel+1]));
        }

        for (edge* e = V[u]; e; e = e->next) {
            int v = e->v;
            int f = fuel - e->d;
            if (f >= 0 && !vis[v][f] && dp[v][f] > cost) {
                dp[v][f] = cost;
                Q.push(ST(v, f, cost));
            }
        }
    }
    return -1;
}

int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 0; i < n; i++)
            scanf("%d", &price[i]);

        EC = 0;
        memset(V, 0, sizeof(V));
        for (int i = 0; i < m; i++) {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            addedge(u, v, d);
            addedge(v, u, d);
        }
        int cases;
        scanf("%d", &cases);
        while (cases--) {
            int vol, s, t;
            scanf("%d%d%d", &vol, &s, &t);

            for (int i = 0; i <= n; i++)
                for (int j = 0; j <= vol; j++)
                    dp[i][j] = INFS, vis[i][j] = false;

            int ans = bfs(s, t, vol);
            if (ans != -1)
                printf("%d\n", ans);
            else
                printf("impossible\n");
        }
    }

    return 0;
}