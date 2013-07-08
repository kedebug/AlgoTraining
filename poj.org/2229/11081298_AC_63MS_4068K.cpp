
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int M = 1000000000;
const int MAXN = 1000010;

int dp[MAXN];

int main()
{
    int n;
    scanf("%d", &n);
    dp[0] = dp[1] = 1;

    for (int i = 2; i <= n; ++i)
        if (i & 0x01)
            dp[i] = dp[i-1];
        else
            dp[i] = (dp[i-2] + dp[i>>1]) % M;

    printf("%d\n", dp[n]);
	return 0;
}