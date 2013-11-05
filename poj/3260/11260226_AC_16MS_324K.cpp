
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

inline int BinarySearch(int arr[], int l, int r, int val)
{
    while (l <= r)
    {
        int m = (l + r) >> 1;
        if (arr[m] > val)
            r = m - 1;
        else
            l = m + 1;
    }
    return l - 1;
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
        int la = 0, ra = -1;
        int lb = 0, rb = -1;
        for (int v = rem, i = 0; v <= vol; v += w, ++i)
        {
            if (la + n == ra && A[la] == B[lb])
                ++la, ++lb;
            else if (la + n == ra)
                ++la;

            ++ra;
            if (dp[v] != INFS)
                A[ra] = dp[v] - i * val;
            else
                A[ra] = INFS;

            //while (lb <= rb && A[ra] < B[rb])
            //    --rb;

            if (lb <= rb)
                rb = BinarySearch(B, lb, rb, A[ra]);
            B[++rb] = A[ra];

            dp[v] = min(dp[v], B[lb] + i * val) ;
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