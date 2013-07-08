
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int maxn = 55;

unsigned long long gcd(unsigned long long a, unsigned long long b)
{
    unsigned long long temp;
    if (a < b)
        temp = a, a = b, b = temp;
    while (b)
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main()
{
    bool flag[maxn][maxn];
    unsigned long long dp[maxn][maxn];
    int n, m;
    int i, j;
    char ch;

    scanf("%d %d", &n, &m);

    memset(flag, false, sizeof(flag));
    memset(dp, 0, sizeof(dp));

    for (i = 1; i <= n; ++i)
    {
        for (j = 1; j <= i;)
        {
            scanf("%c", &ch);
            if (ch == '*')
                flag[i][j++] = true;
            else if (ch == '.')
                ++j;
        }
    }
    //if (flag[1][1])
        dp[1][1] = 1;
    for (i = 2; i <= n + 1; ++i)
    {
        for (j = 1; j <= i; ++j)
        {
            if (flag[i-1][j-1])
                dp[i][j] += dp[i-1][j-1];
            if (flag[i-1][j])
                dp[i][j] += dp[i-1][j];
            if (i > 2 && j > 1 && !flag[i-2][j-1])
                dp[i][j] += dp[i-2][j-1] << 2;
        }
    }

    unsigned long long a, b, temp;
    if (dp[n+1][m+1] == 0)
        printf("0/%lld\n", ((unsigned long long)1 << n));
    else
    {
        a = dp[n+1][m+1];
        b = ((unsigned long long)1 << n);
        temp = gcd(a, b);
        printf("%lld/%lld\n", a / temp, b / temp);
    }
    return 0;
}