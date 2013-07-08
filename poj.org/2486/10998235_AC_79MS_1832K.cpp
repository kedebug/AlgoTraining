
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;
#define max(a,b) (((a) > (b)) ? (a) : (b))

const int MAXN = 1010;

vector<int> map[MAXN];
int dp[2][MAXN][210];

int val[MAXN];
bool vis[MAXN];

int n, m;

void dfs(int u)
{
    vis[u] = true;
    for (int j = 0; j <= m; ++j)
        dp[0][u][j] = dp[1][u][j] = val[u];

    for (int i = 0; i < map[u].size(); ++i)
    {
        int v = map[u][i];
        if (vis[v])
            continue;
        dfs(v);
        for (int j = m; j >= 0; --j)
        {
            for (int k = 0; k <= j; ++k)
            {
                dp[0][u][j+2] = max(dp[0][u][j+2], dp[0][v][k] + dp[0][u][j-k]);
                dp[1][u][j+2] = max(dp[1][u][j+2], dp[0][v][k] + dp[1][u][j-k]);
                dp[1][u][j+1] = max(dp[1][u][j+1], dp[1][v][k] + dp[0][u][j-k]);
            }
        }
    }
}

int main()
{
    while (scanf("%d %d", &n, &m) != EOF)
    {
        for (int i = 1; i <= n; ++i)
            scanf("%d", &val[i]);

        int a, b;
        for (int i = 1; i <= n; ++i)
            map[i].clear();

        for (int i = 1; i <= n-1; ++i)
        {
            scanf("%d %d", &a, &b);
            map[a].push_back(b);
            map[b].push_back(a);
        }
        memset(vis, false, sizeof(vis));
        memset(dp, 0, sizeof(dp));
        dfs(1);
        printf("%d\n", dp[1][1][m]);
    }
    return 0;
}