
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define min(a,b) (((a) < (b)) ? (a) : (b))
const int MAXN = 210;
char str[MAXN];
int dp[MAXN][MAXN], path[MAXN][MAXN];

void outputstr(int i, int j)
{
    if (i > j)
        return;
    if (i == j)
    {
        if (str[i] == '(' || str[i] == ')')
            printf("()");
        else
            printf("[]");
    }
    else if (path[i][j] == -1)
    {
        printf("%c", str[i]);
        outputstr(i+1, j-1);
        printf("%c", str[j]);
    }
    else
    {
        outputstr(i, path[i][j]);
        outputstr(path[i][j]+1, j);
    }
}

int main()
{
    while (gets(str))
    {
        int len = strlen(str);
        if (len == 0)
        {
            printf("\n");
            continue;
        }
        memset(dp, 0, sizeof(dp));
        memset(path, 0, sizeof(path));

        for (int i = 0; i < len; ++i)
            dp[i][i] = 1;

        for (int k = 1; k < len; ++k)
        {
            for (int i = 0, j = k; j < len; ++i, ++j)
            {
                dp[i][j] = INT_MAX;
                if ((str[i] == '(' && str[j] == ')') || (str[i] == '[' && str[j] == ']'))
                    if (dp[i][j] > dp[i+1][j-1])
                        dp[i][j] = dp[i+1][j-1], path[i][j] = -1;

                for (int p = i; p < j; ++p)
                    if (dp[i][j] > dp[i][p] + dp[p+1][j])
                        dp[i][j] = dp[i][p] + dp[p+1][j], path[i][j] = p;
            }
        }
        outputstr(0, len - 1);
        printf("\n");
    }
    return 0;
}