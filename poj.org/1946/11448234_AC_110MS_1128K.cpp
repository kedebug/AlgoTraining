
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int INFS = 0x3fffffff;
int dp[25][MAXN][MAXN], N, E, D;

int main() {
    while (~scanf("%d%d%d", &N, &E, &D)) {
        for (int i = 1; i <= N; i++)
            for (int e = 0; e <= E; e++)
                for (int d = 0; d <= D; d++)
                    dp[i][e][d] = INFS;
        dp[1][0][0] = 0;
        for (int i = 1; i <= N; i++) {
            for (int e = 1; e <= E; e++) {
                for (int d = 1; d <= D; d++) {
                    for (int x = 1; ; x++) {
                        int coste = x * x, costd = x;
                        if (coste > e || costd > d) break;
                        for (int k = 1; k*coste <= e && k*costd <= d; k++)
                            dp[i][e][d] = min(dp[i][e][d], dp[i][e-coste*k][d-costd*k] + k);
                    }
                    dp[i+1][d][d] = min(dp[i+1][d][d], dp[i][e][d]);
                }
            }
        }
        int ans = INFS;
        for (int i = 1; i <= N; i++)
            for (int e = 1; e <= E; e++)
                ans = min(ans, dp[i][e][D]);

        printf("%d\n", ans);
    }
    return 0;
}