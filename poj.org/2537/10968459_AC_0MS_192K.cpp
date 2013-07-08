
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>

const int MAXN = 105;
double dp[MAXN][16];

int main()
{
	int k, n;
	while (scanf("%d %d", &k, &n) != EOF)
	{
		int i, j;

		memset(dp, 0, sizeof(dp));
		for (j = 1; j <= k+1; ++j)
			dp[1][j] = 1;

		for (i = 2; i <= n; ++i)
			for (j = 1; j <= k+1; ++j)
					dp[i][j] = dp[i-1][j-1] + dp[i-1][j] + dp[i-1][j+1];

		double ans = 0;
		for (j = 1; j <= k+1; ++j)
			ans += dp[n][j];
		
		printf("%.5lf\n", ans * 100 / pow(k+1.0, n));
	}
	return 0;
}