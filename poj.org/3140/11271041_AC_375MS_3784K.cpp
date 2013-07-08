
#include <iostream>
#include <algorithm>
using namespace std;

#define LL long long int

const int MAXN = 100010;
const LL INFS = 0x3fffffff3fffffff;

struct edge {
    int v;
    edge *next;
} *V[MAXN], ES[MAXN * 2] ;

int EC;
LL dp[MAXN], N[MAXN], sum;
bool vis[MAXN];

inline void addedge(int a, int b)
{
    ES[++EC].next = V[a];
    V[a] = ES + EC; V[a]->v = b;
}

void treedp(int u)
{
    dp[u] = N[u];
    vis[u] = true;

    for (edge* e = V[u]; e; e = e->next)
    {
        if (vis[e->v])
            continue;

        treedp(e->v);
        dp[u] += dp[e->v];
    }

}

LL solve(int n)
{
    LL ans = INFS;
    for (int u = 1; u <= n; ++u)
        for (edge* e = V[u]; e; e = e->next)
            ans = min(ans, _abs64(sum - dp[e->v] * 2));
    return ans;
}

int main()
{
    int n, m, cc = 0;
    while (scanf("%d %d", &n, &m) && n && m)
    {
        sum = 0, EC = 0;

        for (int i = 1; i <= n; ++i)
            scanf("%lld", &N[i]), sum += N[i];

        memset(dp, 0, sizeof(dp));
        memset(V, 0, sizeof(V));
        memset(vis, false, sizeof(vis));

        for (int i = 0; i < m; ++i)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            addedge(a, b);
            addedge(b, a);
        }

        treedp(1);
        LL ans = solve(n);

        printf("Case %d: %lld\n", ++cc, ans);
    }
    return 0;
}