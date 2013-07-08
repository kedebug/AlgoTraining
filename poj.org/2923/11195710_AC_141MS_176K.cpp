
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int w[20];
int n, C1, C2;
int dp[1100], state[1100];
bool pack[1100];

bool judge(int s)
{
    int sum = 0;
    
    memset(pack, false, sizeof(pack));
    pack[0] = true;

    for (int i = 0; i < n; ++i)
        if (s & (1 << i))
        {
            sum += w[i];
            for (int v = C1; v >= w[i]; --v)
                if (pack[v-w[i]])
                    pack[v] = true;
        }
    for (int v = 0; v <= sum; ++v)
        if (pack[v] && sum - v <= C2)
            return true;

    return false;
}

int main()
{
    int cases;
    int cnt = 0;
    scanf("%d", &cases);
    while (cases--)
    {
        scanf("%d %d %d", &n, &C1, &C2);
        for (int i = 0; i < n; ++i)
            scanf("%d", &w[i]);

        int m = 0;
        memset(dp, 0x3f, sizeof(dp));
        memset(state, 0, sizeof(state));

        for (int i = 0; i <= (1<<n)-1; ++i)
            if (judge(i))
                state[m++] = i;

        dp[0] = 0;
        for (int i = 0; i < m; ++i)
            for (int s = (1<<n)-1-state[i]; s >= 0; --s)
                if (!(s & state[i]))
                    dp[s | state[i]] = min(dp[s | state[i]], dp[s] + 1);

        printf("Scenario #%d:\n%d\n\n", ++cnt, dp[(1<<n)-1]);
    }
    return 0;
}