#include <stdio.h>
#include <string.h>

/* dp[i][j] 表示选到第i件设备，带宽为j 的最小费用 */
int dp[101][1000];

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int main()
{
    int t, n, m, maxb, b[101], p[101];
    //freopen("input", "r", stdin);
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        maxb = 0;
        for (int i = 0; i < 101; i++)
            for (int j = 0; j < 1001; j++)
                dp[i][j] = 0xfffffff;

        for (int i = 1; i <= n; i++) {
            scanf("%d", &m);
            for (int j = 1; j <= m; j++) {
                scanf("%d %d", &b[j], &p[j]);
                maxb = max(maxb, b[j]);
            }

            if (i == 1) {
                for (int k = 1; k <= m; k++) 
                    if (dp[1][b[k]] > p[k])
                        dp[i][b[k]] = p[k];
                continue;
            }

            for (int j = 0; j <= maxb; j++) {
                if (dp[i-1][j] != 0xfffffff)
                    for (int k = 1; k <= m; k++) {
                        int tb = min(j, b[k]);
                        dp[i][tb] = min(dp[i][tb], dp[i-1][j]+p[k]);
                    }
            }
        }

        /*for (int i = 1; i <= n; i++)
            for (int j = 0; j <= maxb; j++)
                if (dp[i][j] != 0xfffffff)
                    printf("%d %d %d\n", i, j, dp[i][j]);
        */
        double ans = 0, temp;
        for (int j = 0; j <= maxb; j++) {
            if (dp[n][j] != 0xfffffff) {
                temp = 1.0*j/dp[n][j];
                if (ans < temp)
                    ans = temp;
            }
        }

        printf("%.3lf\n", ans);
    }

    return 0;
}