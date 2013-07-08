
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 160;
const int INFS = 0x3fffffff;
int dp[MAXN][MAXN], U[MAXN], V[MAXN];
bool vis[MAXN];

void treedp(int u, int vol, int n)
{
    for (int v = 0; v <= vol; ++v)
        dp[u][v] = INFS;
    dp[u][1] = 0;

    for (int i = 1; i < n; ++i)
    {
        if (u == U[i])
        {
            treedp(V[i], vol, n);
            for (int v = vol; v >= 0; --v)
            {
                int ans = INFS;
                if (dp[u][v] != INFS)
                    ans = dp[u][v] + 1;
                for (int p = 0; p <= v; ++p)
                    if (dp[u][p] != INFS && dp[V[i]][v - p] != INFS)
                        ans = min(ans, dp[u][p] + dp[V[i]][v - p]);
                dp[u][v] = ans;
            }
        }
    }
}

int main()
{
    int n, p;
    while (scanf("%d %d", &n, &p) != EOF)
    {
        memset(vis, false, sizeof(vis));
        for (int i = 1; i < n; ++i)
        {
            scanf("%d %d", &U[i], &V[i]);
            vis[V[i]] = true;
        }

        int rt;
        for (int i = 1; i <= n; ++i)
            if (!vis[i])
                rt = i;

        treedp(rt, p, n);

        int ans = dp[rt][p];
        for (int i = 1; i <= n; ++i)
            if (dp[i][p] < ans)
                ans = dp[i][p] + 1;

        printf("%d\n", ans);
    }
    return 0;
}