
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 110;
const int INFS = 0x3FFFFFFF;

int cost[MAXN], arrival[MAXN], deadline[MAXN];
int N, begtime, endtime, ans;
vector<int> G[260];

void dfs(int t, int worktime) {
    while (t <= endtime && !G[t].size())
        ++t;
    
    if (t > endtime) {
        ans = min(ans, worktime);
        return ;
    }

    for (int i = 0; i < G[t].size(); i++) {
        int j = G[t][i];
        dfs(t + cost[j], worktime + cost[j]);
    }
}

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
        ans = INFS;
        dfs(begtime, 0);
        printf("%d\n", ans);
    }
    return 0;
}