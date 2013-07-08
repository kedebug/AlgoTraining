#include <iostream>
#include <algorithm>
using namespace std;

const int MAXD = 10010;
const int MAXN = 150;
const int INFS = 0x3fffffff;

int dp[MAXD << 2], A[MAXD << 2], B[MAXD << 2];
int V[MAXN], C[MAXN];

void ZeroOnePack(int w, int val, int vol)
{
    for (int v = vol; v >= w; --v)
        if (dp[v - w] != INFS)
            dp[v] = min(dp[v], dp[v - w] + val);
}

void CompletePack(int w, int val, int vol)
{
    for (int v = w; v <= vol; ++v)
        if (dp[v - w] != INFS)
            dp[v] = min(dp[v], dp[v - w] + val);
}

void MultiplePack(int w, int val, int n, int vol)
{
    if (n == 1)
    {
        ZeroOnePack(w, val, vol);
        return ;
    }
    if (w * n >= vol)
    {
        CompletePack(w, val, vol);
        return ;
    }

    for (int rem = 0; rem < w; ++rem)
    {
        int LA = 0, RA = -1;
        int LB = 0, RB = -1;
        for (int i = 0; i <= vol / w; ++i)
        {
            if (LA + n == RA && A[LA] == B[LB])
                ++LA, ++LB;
            else if (LA + n == RA)
                ++LA;

            ++RA;
            if (dp[rem + i * w] != INFS)
                A[RA] = dp[rem + i * w] - i * val;
            else
                A[RA] = INFS;

            while (LB <= RB && A[RA] < B[RB])
                --RB;
            B[++RB] = A[RA];

            dp[rem + i * w] = min(dp[rem + i * w], B[LB] + i * val) ;
        }
    }
}

int main()
{
    int n, vol;
    while (scanf("%d %d", &n, &vol) != EOF)
    {
        int vmax = 0;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &V[i]);
            vmax = max(vmax, V[i]);
        }
        for (int i = 0; i < n; ++i)
            scanf("%d", &C[i]);
        vmax >>= 1;
        vmax *= vmax;
        vmax += vol;

        dp[0] = 0;
        for (int v = 1; v <= vmax; ++v)
            dp[v] = INFS;

        for (int i = 0; i < n; ++i)
            MultiplePack(V[i], 1, C[i], vmax);

        for (int i = 0; i < n; ++i)
            for (int v = vmax - V[i]; v >= 0; --v)
                dp[v] = min(dp[v], dp[v + V[i]] + 1);

        if (dp[vol] != INFS)
            printf("%d\n", dp[vol]);
        else
            printf("-1\n");
    }
    return 0;
}