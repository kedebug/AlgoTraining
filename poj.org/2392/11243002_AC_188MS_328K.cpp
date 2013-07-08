
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 410;
const int MAXD = 40010;

struct BlockInfo {
    int h, a, c;
    bool operator < (const BlockInfo& other)
    { return a < other.a; }
} type[MAXN] ;

int dp[MAXD];

void ZeroOnePack(int w, int val, int vol)
{
    for (int v = vol; v >= w; --v)
        dp[v] = max(dp[v], dp[v - w] + val);
}

void CompletePack(int w, int val, int vol)
{
    for (int v = w; v <= vol; ++v)
        dp[v] = max(dp[v], dp[v - w] + val);
}

void MultiplyPack(int w, int val, int num, int vol)
{
    if (w * num >= vol)
    {
        CompletePack(w, val, vol);
        return ;
    }

    int k = 1; 
    while (k <= num)
    {
        ZeroOnePack(w * k, val * k, vol);
        num -= k;
        k <<= 1;
    }
    if (num)
        ZeroOnePack(w * num, val * num, vol);
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d %d %d", &type[i].h, &type[i].a, &type[i].c);

    sort(type, type + n);

    for (int i = 0; i < n; ++i)
    {
        MultiplyPack(type[i].h, type[i].h, type[i].c, type[i].a);

        for (int v = type[i].a; v <= type[n-1].a; ++v)
            dp[v] = dp[type[i].a];
    }

    printf("%d\n", dp[type[n-1].a]);
    return 0;
}