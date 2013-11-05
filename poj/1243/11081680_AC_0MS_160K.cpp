
#include <cstdio>
#include <cstdlib>
#include <cstring>

int dp[32][32];

int solve(int i, int j)
{
    if (dp[i][j] != -1)
        return dp[i][j];

    if (j >= i)
        j = i - 1;

    dp[i][j] = solve(i-1, j-1) + 1 + solve(i-1, j);
    return dp[i][j];
}

int main()
{
    int G, L;
    int cases = 0;
    while (scanf("%d %d", &G, &L) && G)
    {
        memset(dp, -1, sizeof(dp));

        for (int i = 0; i <= G; ++i)
            dp[i][0] = i;
        
        if (L >= G)
            L = G - 1;
        solve(G, L);
        
        printf("Case %d: %d\n", ++cases, dp[G][L]);
    }
	return 0;
}