
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define max(a, b)   ((a) > (b) ? (a) : (b))
const int MAXN = 50005;
int a[MAXN];
int dp[MAXN][4];

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, m;
        int i, j;
        scanf("%d", &n);
        a[0] = 0;
        for (i = 1; i <= n; ++i)
            scanf("%d", &a[i]), a[i] += a[i-1];
        scanf("%d", &m);

        memset(dp, 0, sizeof(dp));
        for (i = 1; i <= n; ++i)
        {
            for (j = 1; j <= 3; ++j)
            {
                int k = i - m;
                if (k < 0)
                    k = 0;
                dp[i][j] = max(dp[i-1][j], dp[k][j-1] + a[i] - a[k]);
            }
        }
        printf("%d\n", dp[n][3]);
    }
    return 0;
}