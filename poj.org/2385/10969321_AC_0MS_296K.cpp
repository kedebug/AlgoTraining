

#include <cstdio>
#include <cstdlib>
#include <cstring>

#define max(a, b)  ((a) > (b) ? (a) : (b))

int dp[1010][32];  
int tree[1010];  

int main()
{
    int t, w;
    while (scanf("%d %d", &t, &w) != EOF)
    {
        int i, j;
        for (i = 1; i <= t; ++i)
            scanf("%d", &tree[i]);
        memset(dp, 0, sizeof(dp));

        if (tree[1] == 1)
            dp[1][0] = 1;
        dp[1][1] = 1;

        for (i = 2; i <= t; ++i)
        {
            for (j = 0; j <= w; ++j)
            {
                if (j == 0)
                    dp[i][j] = dp[i-1][j] + tree[i] % 2;
                dp[i][j] = max(dp[i][j], dp[i-1][j] + (j%2+1 == tree[i]));  //
                dp[i][j] = max(dp[i][j], dp[i-1][j-1] + (j%2 == tree[i]));
                dp[i][j] = max(dp[i][j], dp[i-1][j-1] + (j%2+1 == tree[i]));
            }
        }
        printf("%d\n", dp[t][w]);
    }
    return 0;
}