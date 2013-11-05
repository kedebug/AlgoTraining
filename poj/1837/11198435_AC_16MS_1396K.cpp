
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxd = 15000;
const int maxn = 21;

int h[maxn], w[maxn];
int dp[maxn][maxd];

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; ++i)
        scanf("%d", &h[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &w[i]);

    memset(dp, 0, sizeof(dp));
    dp[0][maxd>>1] = 1;

    for (int i = 1; i <= n; ++i)
        for (int v = 0; v <= maxd; ++v)
            if (dp[i-1][v])
                for (int j = 0; j < m; ++j)
                    dp[i][v+w[i]*h[j]] += dp[i-1][v];

    printf("%d\n", dp[n][maxd>>1]);
    return 0;
}