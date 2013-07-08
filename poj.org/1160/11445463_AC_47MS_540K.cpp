
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 310;
const int INFS = 0x3fffffff;

int dp[MAXN][MAXN], cost[MAXN][MAXN], x[MAXN];
int vill, office;

int calccost(int i, int j) {
    int ans = 0;
    while (i < j) {
        ans += x[j] - x[i];
        j--, i++;
    }
    return ans;
}

int workout() {
    for (int i = 0; i <= office; i++)
        for (int j = 0; j <= vill; j++)
            dp[i][j] = INFS;
    dp[0][0] = 0;

    for (int i = 1; i <= office; i++) {
        for (int j = i; j <= vill; j++) {
            for (int k = 0; k < j; k++)
                dp[i][j] = min(dp[i][j], dp[i-1][k] + cost[k+1][j]);
        }
    }
    return dp[office][vill];
}

int main() {
    while (~scanf("%d%d", &vill, &office)) {
        x[0] = 0;
        for (int i = 1; i <= vill; i++)
            scanf("%d", &x[i]);

        for (int i = 1; i <= vill; i++)
            for (int j = i; j <= vill; j++)
                cost[i][j] = calccost(i, j);

        printf("%d\n", workout());
    }
    return 0;
}