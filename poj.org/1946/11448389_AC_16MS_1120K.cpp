
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int INFS = 0x3fffffff;
int dp[25][MAXN][MAXN], N, E, D;

int main() {
    while (~scanf("%d%d%d", &N, &E, &D)) {
        for (int i = 1; i <= N; i++)
            for (int d = 0; d <= D; d++) 
                for (int e = 0; e <= E; e++)
                    dp[i][d][e] = INFS;
        dp[1][0][0] = 0;
        for (int i = 1; i <= N; i++) {
            for (int d = 1; d <= D; d++) {
                for (int e = 1; e <= E; e++) {
                    for (int k = 1; k*k <= e && k <= d; k++) 
                        dp[i][d][e] = min(dp[i][d][e], dp[i][d-k][e-k*k] + 1);
                    dp[i+1][d][d] = min(dp[i+1][d][d], dp[i][d][e]);
                }
            }
        }
        int ans = INFS;
        for (int e = 1; e <= E; e++)
            ans = min(ans, dp[N][D][e]);
        printf("%d\n", ans);
    }
    return 0;
}