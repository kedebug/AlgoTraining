
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

const int MAXD = 10010;
const int INFS = 0x3fffffff;

int dp[MAXD];

int main()
{
    int cases;
    scanf("%d",&cases);
    while (cases--)
    {
        int E, F, n;
        scanf("%d %d %d", &E, &F, &n);

        dp[0] = 0;
        for (int i = 1; i <= F - E; ++i)
            dp[i] = INFS;

        for (int i = 0; i < n; ++i)
        {
            int value, weight;
            scanf("%d %d", &value, &weight);

            for (int v = weight; v <= F - E; ++v)
                if (dp[v - weight] != INFS)
                    dp[v] = min(dp[v], dp[v - weight] + value);
        }

        if (dp[F - E] != INFS)
            printf("The minimum amount of money in the piggy-bank is %d.\n", dp[F - E]);
        else
            printf("This is impossible.\n");
    }
    return 0;
}