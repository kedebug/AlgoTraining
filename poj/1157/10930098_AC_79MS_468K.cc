
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define max(a,b)  (((a) > (b)) ? (a) : (b))
const int maxn = 110;
const int inf = 100000;
int an[maxn][maxn], dp[maxn][maxn];

int main()
{
    int i, j, k;
    int f, v;
    while (scanf("%d %d", &f, &v) != EOF)
    {
        for (i = 1; i <= f; ++i)
        {
            for (j = 1; j <= v; ++j)
            {
                scanf("%d", &an[i][j]);
            }
        }
        memset(dp, 0, sizeof(dp));
        int t = an[1][1];
        dp[1][1] = an[1][1];
        for (i = 2; i <= v; ++i)
            if (t >= an[1][i])
                dp[1][i] = t;
            else
                dp[1][i] = an[1][i], t = an[1][i];

        for (i = 2; i <= f; ++i)
        {
            for (j = i; j <= v; ++j)
            {
                if (j == i)
                    dp[i][j] = dp[i-1][j-1] + an[i][j];
                else
                    dp[i][j] = max(dp[i][j-1], dp[i-1][j-1] + an[i][j]);
            }
        }
        printf("%d\n", dp[f][v]);
    }
    return 0;
}