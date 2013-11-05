
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 140000;
int dp[maxn];

int main()
{
    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        int vol, y, n;
        int bond[12], value[12];

        scanf("%d %d %d", &vol, &y, &n);

        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d", &bond[i], &value[i]);
            bond[i] /= 1000;
        }

        int ret = vol;
        for (int i = 0; i < y; ++i)
        {
            vol = ret / 1000;

            for (int j = 0; j < n; ++j)
            {
                for (int w = bond[j]; w <= vol; ++w)
                    dp[w] = max(dp[w], dp[w - bond[j]] + value[j]);
            }
            ret += dp[vol];
            memset(dp, 0, sizeof(dp));
        }
        printf("%d\n", ret);
    }
    return 0;
}