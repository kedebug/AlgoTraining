
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 210;

int dp[MAXN][MAXN][MAXN];
int color[MAXN], len[MAXN], pre[MAXN], table[MAXN], block[MAXN];

int solvedp(int l, int r, int k) {
    if (l > r) 
        return 0;

    if (dp[l][r][k] != -1)
        return dp[l][r][k];
    
    if (l == r) {
        return dp[l][r][k] = (len[r]+k)*(len[r]+k);
    }
    int ans;
    ans = solvedp(l, r-1, 0) + (len[r]+k)*(len[r]+k);

    for (int i = pre[r]; i >= l; i = pre[i]) {
        if (color[i] == color[r]) {
            ans = max(ans, solvedp(l, i, len[r]+k) + solvedp(i+1, r-1, 0));
        }
    }
    return dp[l][r][k] = ans;
}

int main() {
    int cases, cc = 0;
    scanf("%d", &cases);
    while (cases--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &block[i]);
        block[n] = n + 1;
        int colcnt = 0, calc = 1;
        memset(table, -1, sizeof(table));
        for (int i = 0; i < n; i++) {
            if (block[i] == block[i+1])
                calc += 1;
            else {
                color[colcnt] = block[i];
                len[colcnt] = calc;
                pre[colcnt] = table[block[i]];
                table[block[i]] = colcnt;
                calc = 1;
                colcnt += 1;
            }
        }
        memset(dp, -1, sizeof(dp));
        int ans = solvedp(0, colcnt - 1, 0);
        printf("Case %d: %d\n", ++cc, ans);
    }
    return 0;
}