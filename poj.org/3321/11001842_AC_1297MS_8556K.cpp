
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 100010;

vector<vector<int>> G(MAXN);
bool vis[MAXN];
bool apple[MAXN];
int high[MAXN], low[MAXN];
int lowb[MAXN];
int c[MAXN];
int n, count;

inline int lowbit(int x)
{
    return x & (-x);
}

void dfs(int u)
{
    vis[u] = true;
    low[u] = count;
    
    for (int i = 0; i < G[u].size(); ++i)
    {
        int v = G[u][i];
        if (!vis[v])
            dfs(v);
    }
    high[u] = count++;
}

int sum(int p)
{
    int ans = 0;
    for (int i = p; i > 0; i -= lowb[i])
        ans += c[i];
    return ans;
}

inline void update(int p)
{
    int d;
    if (apple[p])
        d = -1;
    else
        d = 1;
    apple[p] ^= true;
    for (int i = p; i <= n; i += lowb[i])
        c[i] += d;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        c[i] = lowbit(i), apple[i] = true, vis[i] = false, lowb[i] = c[i];

    for (int i = 1; i < n; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
    }
    count = 1;
    dfs(1);

    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        char s[10];
        int u;
        scanf("%s %d", s, &u);
        if (s[0] == 'Q')
            printf("%d\n", sum(high[u]) - sum(low[u]-1));
        else if (s[0] == 'C')
            update(high[u]);
    }
    return 0;
}