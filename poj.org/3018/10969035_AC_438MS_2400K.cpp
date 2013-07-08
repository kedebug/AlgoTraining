
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#define max(a, b)  ((a) > (b) ? (a) : (b))
int box[512][1005];
bool map[512][512]; // map[i][j] : put i into j
int n, d;

bool judge(int a, int b)
{
    int i;
    for (i = 0; i < d; ++i)
        if (box[a][i] >= box[b][i])
            return false;
    return true;
}

bool init()
{
    int i, j;
    bool flag = false;

    memset(map, false, sizeof(map));

    for (i = 2; i <= n; ++i)
        if (judge(1, i))
            map[1][i] = true, flag = true;

    if (!flag)
        return false;

    for (i = 2; i <= n; ++i)
        for (j = 2; j <= n; ++j)
            if (judge(i, j))
                map[i][j] = true;
    return true;
}

int main()
{
    while (scanf("%d %d", &n, &d) != EOF)
    {
        int i, j;
        ++n;
        for (i = 1; i <= n; ++i)
        {
            for (j = 0; j < d; ++j)
                scanf("%d", &box[i][j]);
            sort(box[i], box[i] + d);
        }

        if (!init()) 
        {
            printf("Please look for another gift shop!");  
            continue;  
        }

        int dp[512];
        dp[1] = 0;
        for (i = 2; i <= n; ++i)
            dp[i] = -1;
        for (i = 1; i <= n; ++i)
            for (j = 1; j <= n; ++j)
                if (map[i][j] && dp[i] != -1)
                    dp[j] = max(dp[j], dp[i] + 1);
        int ans = dp[1];
        for (i = 2; i <= n; ++i)
            if (dp[i] > ans)
                ans = dp[i];
        printf("%d\n", ans);
    }
    return 0;
}