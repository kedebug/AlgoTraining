
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAXN = 12;

int main()
{
    int dp[MAXN][MAXN];
    int t, m, n;
    scanf("%d", &t);

    while (t--)
    {
        memset(dp, 0, sizeof(dp));
        scanf("%d %d", &m, &n);

        int i, j;
        for (i = 1; i <= m; ++i)
            for (j = 1; j <= n; ++j)
                if (i > j)
                    dp[i][j] = dp[i][j-1] + dp[i-j][j];
                else if (i == j)
                    dp[i][j] = dp[i][j-1] + 1;
                else if (i < j)
                    dp[i][j] = dp[i][j-1];
        printf("%d\n", dp[m][n]);
    }
    return 0;
}