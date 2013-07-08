
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <sstream>
using namespace std;

#define min(a,b) (((a) < (b)) ? (a) : (b))
const int MAXN = 210;
const int INF = 1e9;

vector<int> tree[MAXN];
int dp[MAXN][MAXN];             // dp[u][m] 节点u选择m个国家所花费的最小代价
int cost[MAXN], node[MAXN];     // node[i] = 1 represent i is the node of the tree, 0 represent the root of the tree
bool vis[MAXN];
int n, m;

int dfs(int u)
{
    vis[u] = true;              // 对于一张图，用vis来标记，然后dfs，就可以实现遍历了，和树的深度遍历应该没区别
    int child = 1;
    for (int i = 0; i < tree[u].size(); ++i)
    {
        int v = tree[u][i];
        if (vis[v])
            continue;
        child += dfs(v);
    }
    for (int j = 1; j <= n; ++j)
        dp[u][j] = INF;
    dp[u][0] = 0;
    
    for (int i = 0; i < tree[u].size(); ++i)
    {  
        int v = tree[u][i];
        for (int j = n; j > 0; --j)
            for (int k = 0; k <= j; ++k)
                dp[u][j] = min(dp[u][j], dp[u][j-k] + dp[v][k]);
    }
    dp[u][child] = min(dp[u][child], cost[u]);
    return child;
}

int main()
{
    char str[1000];
    while (gets(str) && str[0] != '#')
    {
        sscanf(str, "%d %d", &n, &m);
        for (int i = 0; i <= n; ++i)
            tree[i].clear();

        map<string, int> mapidx;
        int id = 0;

        memset(cost, 0, sizeof(cost));
        memset(node, 0, sizeof(node));

        for (int i = 1; i <= n; ++i)
        {
            scanf("%s", str);
            if (mapidx.find(str) == mapidx.end())
                mapidx[str] = ++id;

            int u = mapidx[str];
            scanf("%d", &cost[u]);

            gets(str);
            stringstream s(str);
            string name;
            
            while (s >> name)
            {
                if (mapidx.find(name) == mapidx.end())
                    mapidx[name] = ++id;
                tree[u].push_back(mapidx[name]);
                ++node[mapidx[name]];
            }
        }
        cost[0] = INF;
        for (int i = 1; i <= n; ++i)
            if (!node[i])
                tree[0].push_back(i);   // tree[0] is the root

        memset(vis, false, sizeof(vis));
        dfs(0);
        int ans = INF;
        for (int j = m; j <= n; ++j)
            if (dp[0][j] < ans)
                ans = dp[0][j];

        printf("%d\n", ans);
    }
    return 0;
}