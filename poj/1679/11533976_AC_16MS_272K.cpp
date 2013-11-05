
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int INFS = 0x3FFFFFFF;

int d[MAXN], p[MAXN], map[MAXN][MAXN], dp[MAXN][MAXN];
bool vis[MAXN];

int prim(int n) {
    int ans = 0;

    for (int i = 1; i <= n; i++)
        d[i] = map[1][i], p[i] = 1;
    memset(dp, 0, sizeof(dp));
    memset(vis, false, sizeof(vis));

    vector<int> inq;
    vis[1] = true; inq.push_back(1);
    for (int k = 1; k < n; k++) {
        int j, temp = INFS;
        for (int i = 1; i <= n; i++) {
            if (!vis[i] && d[i] < temp)
                j = i, temp = d[i];
        }
        vis[j] = true; ans += temp;

        for (int i = 0; i < inq.size(); i++)
            dp[j][inq[i]] = dp[inq[i]][j] = max(temp, dp[inq[i]][p[j]]);
        inq.push_back(j);

        for (int i = 1; i <= n; i++) {
            if (!vis[i] && d[i] > map[i][j])
                d[i] = map[i][j], p[i] = j;
        }
    }
    return ans;
}

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                map[i][j] = (i == j) ? 0 : INFS;
        for (int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            map[a][b] = map[b][a] = c;
        }
        int ans = prim(n);
        int cflag = INFS;
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)
            if (i != j && map[i][j] != INFS && p[i] != j && p[j] != i)
                cflag = min(cflag, map[i][j] - dp[i][j]);
        if (cflag == 0) 
            printf("Not Unique!\n");
        else 
            printf("%d\n", ans);
    }
    return 0;
}