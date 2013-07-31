
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXT = 20 * 12;
const int MAXN = 30;

int dp[MAXN][MAXT], pre[MAXN][MAXT], t[MAXN], f[MAXN], d[MAXN], path[MAXN];
int n, h;

void initDpArray() {
    memset(dp, -1, sizeof(dp));

    for (int j = 0; j <= h; j++)
        dp[0][j] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= h; j++) {
            int fish = 0, sum = f[i];
            for (int k = 0; k + t[i] <= j; k++) {
                if (dp[i-1][j-t[i]-k] == -1) continue;
                dp[i][j] = max(dp[i][j], dp[i-1][j-t[i]-k] + fish);
                fish += sum;
                if (sum > d[i]) sum -= d[i];
                else sum = 0;
            }
        }
    }
}

void getPath(int i, int time) {
    if (i == 1) { 
        path[i] = time * 5;
        return;
    }
    int fish = 0, sum = f[i];
    for (int k = 0; time >= k + t[i]; k++) {
        if (dp[i-1][time-k-t[i]] + fish == dp[i][time]) {
            path[i] = k * 5;
            return getPath(i - 1, time - k - t[i]);
        }
        fish += sum;
        if (sum > d[i]) sum -= d[i];
        else sum = 0;
    }
}

int main() {

    while (scanf("%d", &n) && n) {
        scanf("%d", &h);
        for (int i = 1; i <= n; i++)
            scanf("%d", &f[i]);
        for (int i = 1; i <= n; i++)
            scanf("%d", &d[i]);
        t[1] = 0;
        for (int i = 1; i < n; i++)
            scanf("%d", &t[i+1]);

        h *= 12;
        initDpArray();

        int maxfish = -1, p = -1;
        for (int i = 1; i <= n; i++) {
            if (maxfish < dp[i][h])
                maxfish = dp[i][h], p = i;
        }
        for (int i = p + 1; i <= n; i++)
            path[i] = 0;
        getPath(p, h);

        for(int i = 1; i <= n-1; i++)
            printf("%d, ",path[i]);
        printf("%d\n", path[n]);
        printf("Number of fish expected: %d\n\n", dp[p][h]);
    }
    return 0;
}