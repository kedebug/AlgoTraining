
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 3010;
const int INFS = 0x3fffffff;

struct edge {
    int v, c;
    edge* next;
} *V[MAXN], ES[MAXN * 3];

int EC, N, M, sum[MAXN], dp[MAXN][MAXN];

void addedge(int u, int v, int c)
{
    ES[++EC].next = V[u];
    V[u] = ES + EC; 
    V[u]->v = v, V[u]->c = c;
}

void initdata()
{
    for (int i = 1; i <= N; ++i)
    {
        dp[i][0] = 0;
        for (int j = 1; j <= M; ++j)
            dp[i][j] = -INFS;
    }

    EC = 0;
    memset(V, 0, sizeof(V));

    for (int i = 1; i <= N - M; ++i)
    {
        int k, a, b;
        scanf("%d", &k);
        for (int j = 0; j < k; ++j)
        {
            scanf("%d %d", &a, &b);
            addedge(i, a, b);
            addedge(a, i, b);
        }
    }

    memset(sum, 0, sizeof(sum));
    for (int i = N - M + 1; i <= N; ++i)
        scanf("%d", &dp[i][1]), sum[i] = 1;
}

void treedp(int u, int f)
{
    for (edge* e = V[u]; e; e = e->next)
    {
        if (e->v == f)
            continue;

        treedp(e->v, u);
        sum[u] += sum[e->v];

        for (int i = sum[u]; i >= 1; --i)
            for (int j = 1; j <= i; ++j)
                if (dp[u][i-j] != -INFS && dp[e->v][j] != -INFS)
                    dp[u][i] = max(dp[u][i], dp[u][i-j] + dp[e->v][j] - e->c);
    }
}

int main()
{
    while (scanf("%d %d", &N, &M) != EOF)
    {
        initdata();
        treedp(1, 0);

        int i;
        for (i = M; i >= 0; --i)
            if (dp[1][i] >= 0)
                break ;

        printf("%d\n", i);
    }
    return 0;
}