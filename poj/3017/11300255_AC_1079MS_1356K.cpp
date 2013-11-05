#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

#define LL long long int

const int MAXN = 100010;

int num[MAXN], deq[MAXN];
LL dp[MAXN];
multiset<LL> optset;

int main()
{
    LL N, M;

    scanf("%lld %lld", &N, &M);
    for (int i = 1; i <= N; ++i)
        scanf("%d", &num[i]);

    LL sum = 0;
    int s = 0, e = -1, p = 1;
    bool flag = false;

    optset.clear();
    for (int i = 1; i <= N; ++i)
    {
        if (num[i] > M)
        {
            flag = true;
            break;
        }

        sum += num[i];
        while (sum > M)
            sum -= num[p++];

        while (s <= e && num[i] >= num[deq[e]])
        {
            if (s < e)
                optset.erase(dp[deq[e-1]] + num[deq[e]]);
            --e;
        }

        deq[++e] = i;
        if (s < e)
            optset.insert(dp[deq[e-1]] + num[deq[e]]);

        while (deq[s] < p)
        {
            if (s < e)
                optset.erase(dp[deq[s]] + num[deq[s+1]]);
            ++s;
        }

        dp[i] = dp[p-1] + num[deq[s]];
        if (s < e && dp[i] > *optset.begin())
            dp[i] = *optset.begin();
    }
    if (flag)
        dp[N] = -1;
    printf("%lld\n", dp[N]);
    return 0;
}