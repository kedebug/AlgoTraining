
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int MAXD = 100010;

int A[MAXN], C[MAXN];
bool dp[MAXD], deq[MAXD];

int main()
{
    int n, m;
    while (scanf("%d %d", &n, &m) && n && m >= 0)
    {
        for (int i = 0; i < n; ++i)
            scanf("%d", &A[i]);
        for (int i = 0; i < n; ++i)
            scanf("%d", &C[i]);
        for (int v = 0; v <= m; ++v)
            dp[v] = false;

        int ret = 0;
        dp[0] = true;
        for (int i = 0; i < n; ++i)
        {
            for (int rem = 0; rem < A[i]; ++rem)
            {
                int s = 0, e = 0, sum = 0;
                for (int v = rem; v <= m; v += A[i])
                {
                    if (s + C[i] == e - 1)
                        sum -= deq[s++];

                    deq[e++] = dp[v];
                    sum += dp[v];

                    if (!dp[v] && sum)
                        dp[v] = true, ++ret;
                }
            }
        }
        printf("%d\n", ret);
    }

    return 0;
}