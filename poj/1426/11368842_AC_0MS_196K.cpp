
#include <iostream>
#include <algorithm>
using namespace std;

__int64 dp[110][210];

__int64 solve(int n) {
    int rem = 1;
    __int64 exp = 1;

    memset(dp[0], 0, sizeof(dp[1]));
    dp[0][1] = 1;

    for (int i = 1; i <= 100; i++) {
        exp *= 10;
        rem = (rem * 10) % n;
        for (int j = 0; j < n; j++) {
            dp[i][j] = dp[i-1][j];
        }
        for (int j = 0; j < n; j++) {
            if (dp[i-1][j] || j == 0) {
                int r0 = (j + rem) % n;
                if (dp[i][r0] == 0)
                    dp[i][r0] = exp + dp[i-1][j];
                if (r0 == 0) 
                    return dp[i][r0];
            }
        }
    }
    return 0;
}

int main() {
    int n;
    while (scanf("%d", &n) && n) {
        if (n == 1) 
            printf("1\n");
        else
            printf("%I64d\n", solve(n));
    }
    return 0;
}