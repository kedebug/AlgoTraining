
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

int dp[101][1005];

int main()
{
    int cases, n;
    scanf("%d", &cases);
    while (cases--)
    {
        scanf("%d", &n);
        int b[105], p[105];
        int m;
        int maxb = -1;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < 1005; ++j)
                dp[i][j] = 1e9;

            scanf("%d", &m);
            
            for (int j = 0; j < m; ++j)
            {
                scanf("%d %d", &b[j], &p[j]);
                if (maxb < b[j])
                    maxb = b[j];
            }
            if (i == 0)
            {
                for (int j = 0; j < m; ++j)
                    if (dp[i][b[j]] > p[j])
                        dp[i][b[j]] = p[j];
                continue;
            }
            for (int j = 0; j <= maxb; ++j)
            {
                if (dp[i-1][j] == 1e9)
                    continue;
                for (int k = 0; k < m; ++k)
                {
                    int tb = min(j, b[k]);
                    dp[i][tb] = min(dp[i][tb], dp[i-1][j] + p[k]);
                }
            }
        }
        double ans = 0;
        for (int j = 0; j <= maxb; ++j)
            if (dp[n-1][j] != 1e9)
                ans = max(ans, 1.0 * j / dp[n-1][j]);
        printf("%.3lf\n", ans);
    }

    return 0;
}