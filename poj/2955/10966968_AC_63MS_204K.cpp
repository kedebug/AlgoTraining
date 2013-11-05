#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

const int MAXN = 105;
#define max(a, b)	((a) > (b) ? (a) : (b))

int main()
{
	char str[MAXN];
	int dp[MAXN][MAXN];
	while (scanf("%s", str) && str[0] != 'e')
	{
		int i, j;	// i is the start point, j is the end point
		int p;		// p is the length of region
		int k;
		int len = strlen(str);

		memset(dp, 0, sizeof(dp));
		for (p = 1; p < len; ++p)
		{
			for (i = 0, j = p; j < len; ++i, ++j)
			{
				if ((str[i] == '(' && str[j] ==')') || (str[i] == '[' && str[j] ==']'))
					dp[i][j] = max(dp[i][j], dp[i+1][j-1] + 2);
				for (k = i; k < j; ++k)
					dp[i][j] = max(dp[i][j], dp[i][k] + dp[k+1][j]);
			}
		}
		printf("%d\n", dp[0][len-1]);
	}
	return 0;
}