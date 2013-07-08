
#include <iostream>
#include <algorithm>
using namespace std;

char grid[10][10];
int N, K, ans, dp[2][1<<8];

int main() {
    while (scanf("%d%d", &N, &K)) {
        if (N == -1 && K == -1)
            break ;
        for (int i = 0; i < N; i++)
            scanf("%s", &grid[i][0]);

        int t1 = 1, t2 = 0;
        memset(dp, 0, sizeof(dp));

        dp[0][0] = 1;
        for (int i = 0; i < N; i++) {
            t1 ^= 1, t2 ^= 1;
            for (int s = (1<<N)-1; s >=0 ; s--) {
                dp[t2][s] = dp[t1][s];
                for (int j = 0; j < N; j++)
                    if (grid[i][j] == '#' && !(s & (1<<j)))
                        dp[t2][s|(1<<j)] += dp[t1][s];
            }
        }
        int ans = 0;
        for (int s = 0; s < 1<<N; s++) {
            int m = 0, t = s;
            while (t > 0) {
                t &= (t-1);
                m += 1;
            }
            if (m == K) 
                ans += dp[t2][s];
        }
        printf("%d\n", ans);
    } 
}