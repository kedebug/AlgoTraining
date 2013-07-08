
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int MAXN = 10001;
int a[MAXN];
bool dp[MAXN][101];

int main()
{
    int n, k;
    int i, j;

    scanf("%d %d", &n, &k);

    for (i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        while (a[i] < 0)
            a[i] += k;
        a[i] %= k;
    }
    memset(dp, false, sizeof(dp));
    dp[1][a[1]] = true;
    for (i = 2; i <= n; ++i)
    {
        for (j = 0; j < k; ++j)
        {
            int t1, t2;
            t1 = j - a[i];
            while (t1 < 0)
                t1 += k;
            t2 = j + a[i];
            t2 %= k;
            dp[i][j] = dp[i-1][t1] || dp[i-1][t2];
        }
    }
    if(dp[n][0])
        printf("Divisible\n");
    else
        printf("Not divisible\n");
    return 0;
}
