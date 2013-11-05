#include<stdio.h>
#include<string.h>
#define MAXD 310
#define MAXP 40
int N, P, f[MAXP][MAXD], w[MAXD][MAXD], a[MAXD];
void init()
{
    int i, j, k;
    for(i = 1; i <= N; i ++)
    {
        scanf("%d", &a[i]);
        w[i][i] = 0;
    }
    for(k = 1; k < N; k ++)
        for(i = 1; (j = i + k) <= N; i ++)
            w[i][j] = w[i][j - 1] + a[j] - a[(i + j) / 2];
}
void solve()
{
    int i, j, k;
    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0;
    for(i = 1; i <= P; i ++)
        for(j = i; j <= N; j ++)
            for(k = i - 1; k < j; k ++)
                if(f[i - 1][k] + w[k + 1][j] < f[i][j])
                    f[i][j] = f[i - 1][k] + w[k + 1][j];
    printf("%d\n", f[P][N]);
}
int main()
{
    while(scanf("%d%d", &N, &P) == 2)
    {
        init();
        solve();
    }
    return 0;
}