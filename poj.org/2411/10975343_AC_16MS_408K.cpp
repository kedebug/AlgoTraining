
//
// http://blog.csdn.net/wmn_wmn/article/details/7773167
//
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAXN = 15;
__int64 dp[MAXN][2050];
__int64 ans[MAXN][MAXN];

int row, col;

void init(int state, int p)
{
    if (p == col)
        dp[0][state] = 1;
    if (p < col)        // 该格子竖着铺，2种策略
        init(state << 1, p + 1);
    if (p + 1 < col)    // 该格子横着铺，1种策略，于是要 | 3
        init(state << 2 | 3, p + 2);
}

void dfs(int x, int xstate, int upstate, int p)
{
    if (p == col)
    {
        dp[x][xstate] += dp[x-1][upstate];
        return ;
    }
    if (p < col)
    {
        dfs(x, xstate << 1, upstate << 1 | 1, p + 1);
        dfs(x, xstate << 1 | 1, upstate << 1, p + 1);
    }
    if (p + 1 < col)
    {
        dfs(x, xstate << 2 | 3, upstate << 2 | 3, p + 2);
    }
}

int main()
{
    memset(ans, -1, sizeof(ans));
    while (scanf("%d %d", &row, &col) && row && col)
    {
        if (ans[row][col] != -1)
        {
            printf("%lld\n", ans[row][col]);
            continue;
        }
        if (row * col % 2)
        {
            printf("0\n");
            continue;
        }

        memset(dp, 0, sizeof(dp));
        init(0, 0);
        for (int i = 1; i < row; ++i)
            dfs(i, 0, 0, 0);
        ans[row][col] = ans[col][row] = dp[row-1][(1<<col)-1];
        printf("%lld\n", ans[row][col]);
    }
    return 0;
}