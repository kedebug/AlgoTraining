
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 32;
const int MAXD = 1010;

int w[MAXN], dp[MAXD];

int main()
{
    int cases, cc = 0;
    scanf("%d", &cases);
    while (cases--)
    {
        int n, vol;
        scanf("%d %d", &n, &vol);

        for (int i = 0; i < n; ++i)
            scanf("%d", &w[i]);

        sort(w, w + n);

        int sum = 0, delta = 0;
        for (int i = 0; i < n; ++i)
        {
            memset(dp, 0, sizeof(dp));
            dp[delta] = 1;

            for (int j = i + 1; j < n; ++j)
                for (int v = vol; v >= w[j] + delta; --v)
                    dp[v] += dp[v - w[j]];

            for (int v = vol; v > max(vol - w[i], 0); --v)
                if (v >= delta)
                    sum += dp[v];

            delta += w[i];
        }
        printf("%d %d\n", ++cc, sum);
    }
    return 0;
}