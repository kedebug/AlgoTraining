
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAXN = 500;
char s1[MAXN], s2[MAXN];
int dp[MAXN][MAXN];
#define max(a,b)    (((a) > (b)) ? (a) : (b))
int main()
{
    while (scanf("%s %s", s1 + 1, s2 + 1) == 2)
    {
        int c1, c2;
        int i, j;

        c1 = strlen(s1 + 1);
        c2 = strlen(s2 + 1);

        for (i = 1; i <= c1; ++i)
            for (j = 1; j <= c2; ++j)
                if (s1[i] == s2[j])
                    dp[i][j] = dp[i-1][j-1] + 1;
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

        printf("%d\n", dp[c1][c2]);

        memset(s1, 0, sizeof(s1));
        memset(s2, 0, sizeof(s2));
        memset(dp, 0, sizeof(dp));
    }
    return 0;
}
