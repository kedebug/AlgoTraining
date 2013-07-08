
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int maxn = 110;

int row, col;
int map[maxn][maxn];
int dp[maxn][maxn];

int dfs(int r, int c)
{
    if (dp[r][c])
        return dp[r][c];

    int max_ret = 1;
    int len;

    if (r + 1 <= row && map[r][c] > map[r+1][c])
    {
        len = dfs(r + 1, c) + 1;
        if (len > max_ret)
            max_ret = len;
    }
    if (r - 1 >= 1 && map[r][c] > map[r-1][c])
    {
        len = dfs(r - 1, c) + 1;
        if (len > max_ret)
            max_ret = len;
    }
    if (c + 1 <= col && map[r][c] > map[r][c+1])
    {
        len = dfs(r, c + 1) + 1;
        if (len > max_ret)
            max_ret = len;
    }    
    if (c - 1 >= 1 && map[r][c] > map[r][c-1])
    {
        len = dfs(r, c - 1) + 1;
        if (len > max_ret)
            max_ret = len;
    }
    return max_ret;
}

int main()
{
    int i, j;
    int ans = 0;
    
    scanf("%d %d", &row, &col);

    for (i = 1; i <= row; ++i)
        for (j = 1; j <= col; ++j)
            scanf("%d", &map[i][j]);

    memset(dp, 0, sizeof(dp));
    for (i = 1; i <= row; ++i)
    {
        for (j = 1; j <= col; ++j)
        {
            dp[i][j] = dfs(i, j);
            if (dp[i][j] > ans)
                ans = dp[i][j];
        }
    }
    printf("%d\n", ans);
}