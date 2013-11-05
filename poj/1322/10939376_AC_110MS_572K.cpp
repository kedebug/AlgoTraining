
#include <cstdio>
#include <cstdlib>
#include <cstring>

float p[1005][105];

int main()
{
    int c, n, m, i, j;
    while (scanf("%d", &c) && c)
    {
        scanf("%d %d", &n, &m);
        if (m > c || m > n || (m + n) % 2 != 0)
        {
            printf("0.000\n");
            continue;
        }
        if (n > 1000)
            n = 1000 + n % 2;

        for (j = 0; j <= c; ++j)
            p[0][j] = 0;
        p[0][0] = 1;

        for (i = 1; i <= n; ++i)
        {
            for (j = 0; j <= c; ++j)
            {
                if (j == 0)
                    p[i][j] = p[i-1][j+1] / c;
                else if (j == c)
                    p[i][j] = p[i-1][j-1] / c;
                else
                    p[i][j] = p[i-1][j-1] * (c-j+1) / c + p[i-1][j+1] * (j+1) / c;
            }
        }
        printf("%.3lf\n", p[n][m]);
    }
    return 0;
}