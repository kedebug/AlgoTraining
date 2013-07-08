
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define min(a, b)  ((a) < (b) ? (a) : (b))
const int MAXN = 5005;
char s[MAXN];
short int dp[MAXN][MAXN];

int main()
{
	int n;
	int i, j, p;
	scanf("%d", &n);
	scanf("%s", s);
	
	memset(dp, 0, sizeof(dp));
	for (p = 1; p < n; ++p)
	{
		for (i = 0, j = p; j < n; ++i, ++j)
		{
			if (s[i] == s[j])
				dp[i][j] = dp[i+1][j-1];
			else
				dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1;
		}
	}
	printf("%d\n", dp[0][n-1]);
	return 0;
}