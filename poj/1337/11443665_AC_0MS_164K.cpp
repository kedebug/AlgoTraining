
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 110;
const int INFS = 0x3FFFFFFF;

int cost[MAXN], arrival[MAXN], deadline[MAXN];
int N, begtime, endtime, dp[260];
vector<int> G[260];

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        scanf("%d", &N);
        begtime = INFS, endtime = 0;
        for (int i = 0; i < N; i++) {
            scanf("%d%d%d", &cost[i], &arrival[i], &deadline[i]);
            begtime = min(begtime, arrival[i]);
            endtime = max(endtime, deadline[i]);
        }
        for (int i = begtime; i <= endtime; i++) {
            G[i].clear();
            for (int j = 0; j < N; j++) {
                if (arrival[j] <= i && i+cost[j] <= deadline[j])
                    G[i].push_back(j);
            }
        }
        dp[endtime] = 0;
        for (int t = endtime-1; t >= begtime; t--) {
            if (!G[t].size()) {
                dp[t] = dp[t+1]; continue;
            }
            dp[t] = INFS;
            for (int i = 0; i < G[t].size(); i++) {
                int j = G[t][i];
                dp[t] = min(dp[t], dp[t+cost[j]] + cost[j]);
            }
        }
        printf("%d\n", dp[begtime]);
    }
    return 0;
}