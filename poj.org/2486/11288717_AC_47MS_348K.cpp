
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int MAXD = 210;

struct edge {
    int v;
    edge* next;
} *V[MAXN], ES[MAXN * 2];

int EC, N, K, val[MAXN], dp[2][MAXN][MAXD];
bool vis[MAXN];

void addedge(int u, int v)
{
    ES[++EC].next = V[u];
    V[u] = ES + EC; V[u]->v = v;
}

void initdata(int n)
{
    EC = 0;
    memset(V, 0, sizeof(V));
    memset(vis, false, sizeof(vis));

    for (int i = 1; i <= n; ++i)
        scanf("%d", &val[i]);

    for (int i = 1; i <= n - 1; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        addedge(a, b);
        addedge(b, a);
    }
    memset(dp, 0, sizeof(dp));
}

void treedp(int u, int vol)
{
    vis[u] = true;

    for (int j = 0; j <= vol; ++j)
        dp[0][u][j] = dp[1][u][j] = val[u];

    for (edge* e = V[u]; e; e = e->next)
    {
        int v = e->v;
        if (vis[v])
            continue;

        treedp(v, vol - 1);

        for (int i = vol; i >= 0; --i)
        {
            for (int j = 0; j <= i; ++j)
            {
                dp[1][u][i+2] = max(dp[1][u][i+2], dp[1][v][i-j] + dp[1][u][j]);
                dp[0][u][i+2] = max(dp[0][u][i+2], dp[1][v][i-j] + dp[0][u][j]);
                dp[0][u][i+1] = max(dp[0][u][i+1], dp[0][v][i-j] + dp[1][u][j]);
            }
        }
    }
}

int main()
{
    while (scanf("%d %d", &N, &K) != EOF)
    {
        initdata(N);
        treedp(1, K);
        printf("%d\n", dp[0][1][K]);
    }
    return 0;
}