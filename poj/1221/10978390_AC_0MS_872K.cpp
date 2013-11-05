//
// http://blog.csdn.net/linulysses/article/details/5820916
//
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define min(a, b)  ((a) < (b) ? (a) : (b))
const int MAXN = 301;
__int64 f[MAXN][MAXN];

void init()
{
    memset(f, 0, sizeof(f));
    for (int i = 1; i < 301; ++i)
    {
        for (int j = 1; j <= i; ++j)
            if (j == 1)
                f[i][1] = 1;
            else if (j == i)
                f[i][j] = f[i][j-1] + 1;
            else
                f[i][j] = f[i][j-1] + f[i-j][min(i-j,j)];
    }
}

int main()
{
    __int64 ans;
    int n;
    init();
    while (scanf("%d", &n) && n)
    {
        ans = 0;
        for (int i = 1; i < n; ++i)
            if ((n-i)%2 == 0)
                ans += f[(n-i)>>1][min((n-i)>>1,i)];
        if (n % 2 == 0)
            ans += f[n>>1][n>>1];
        printf("%d %lld\n", n, ans + 1);
    }
    return 0;
}