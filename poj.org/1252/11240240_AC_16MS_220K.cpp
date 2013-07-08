
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 10000;
const int infs = 0x3ffffff;
int dp[maxn + 1];

int main()
{
    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        int w[10];
        for (int i = 0; i < 6; ++i)
            scanf("%d", &w[i]);

        dp[0] = 0;
        for (int v = 1; v < maxn; ++v)
            dp[v] = infs;

        for (int i = 0; i < 6; ++i)
            for (int v = w[i]; v < maxn; ++v)
                if (dp[v - w[i]] != infs)
                    dp[v] = min(dp[v], dp[v - w[i]] + 1);

        for (int i = 0; i < 6; ++i)
            for (int v = maxn - w[i] - 1; v >= 0; --v)
                if (dp[v + w[i]] != infs)
                    dp[v] = min(dp[v], dp[v + w[i]] + 1);

        int ave = 0, maxret = 0;
        for (int v = 1; v <= 100; ++v)
        {
            ave += dp[v];
            maxret = max(maxret, dp[v]);
        }

        double ans = ave;
        ans /= 100;
        printf("%.2lf %d\n", ans, maxret);
    }
    return 0;
}