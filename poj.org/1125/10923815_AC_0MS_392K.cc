
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int maxn = 110;

int an[maxn][maxn];
int dp[maxn][maxn];

void floyd(int n)
{
    int i, j, k;
    for (k = 1; k <= n; ++k)
    {
        for (i = 1; i <= n; ++i)
        {
            //if (i != k) 
            for (j = 1; j <= n; ++j)
            {
               // if (j == k || j == i)
               //     continue;
                if (dp[i][j] > dp[i][k] + dp[k][j])
                    dp[i][j] = dp[i][k] + dp[k][j];
            }
        }
    }
}

int main()
{
    int n;
    int i, j, k;
    while (scanf("%d", &n) && n)
    {
        //memset(an, 0, sizeof(an));
        //memset(dp, 0, sizeof(dp));
        for (i = 1; i <= n; ++i)
        {
            for (j = 1; j <= n; ++j)
            {
                if (i != j)
                    dp[i][j] = 100000;
                else
                    dp[i][j] = 0;
            }
        }

        for (i = 1; i <= n; ++i)
        {
            int e, t;
            scanf("%d", &k);
            for (j = 0; j < k; ++j)
            {
                scanf("%d %d", &e, &t);
                an[i][e] = t;
                dp[i][e] = t;
            }
        }
        floyd(n);
        int ans;
        int s, e;
        int tmax;

        ans = 100000;

        for (i = 1; i <= n; ++i)
        {
            tmax = 0;
            for (j = 1; j <= n; ++j)
                if (tmax < dp[i][j])
                    tmax = dp[i][j];
            if (tmax < ans)
                ans = tmax, s = i;
        }
        if (ans != 100000)
            printf("%d %d\n", s, ans);
        else
            printf("disjoint\n");
    }
    return 0;
}