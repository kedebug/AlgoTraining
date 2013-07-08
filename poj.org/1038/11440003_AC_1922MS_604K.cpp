
#include <iostream>
#include <algorithm>
using namespace std;

bool grid[160][12];
int row, col, Q[2][12], dp[2][60000];

void backstate(int s, int f[]) {
    for (int i = 0; i < col; i++) {
        f[i] = s % 3; s /= 3;
    }
}

int getstate(int f[]) {
    int ans = 0;
    for (int i = col-1; i >= 0; i--) {
        ans *= 3;
        ans += f[i];
    }
    return ans;
}

int T1, T2;

void dfs(int i, int count, int state) {
    if (i > col - 1)
        return;

    if (i+2 < col && Q[1][i] == 0 && Q[1][i+1] == 0 && Q[1][i+2] == 0) {
        Q[1][i] = Q[1][i+1] = Q[1][i+2] = 2;
        int now = getstate(Q[1]);
        dp[T2][now] = max(dp[T2][now], count+1);
        dfs(i+3, count+1, now);
        Q[1][i] = Q[1][i+1] = Q[1][i+2] = 0;
    }

    if (i+1 < col && Q[1][i] == 0 && Q[1][i+1] == 0 && Q[0][i] == 0 && Q[0][i+1] == 0) {
        Q[1][i] = Q[1][i+1] = 2;
        int now = getstate(Q[1]);
        dp[T2][now] = max(dp[T2][now], count+1);
        dfs(i+2, count+1, now);
        Q[1][i] = Q[1][i+1] = 0;
    }

    dp[T2][state] = max(dp[T2][state], dp[T1][getstate(Q[0])]);
    dfs(i+1, count, state);
}

int solvedp() {
    int endstate = 1;
    for (int i = 0; i < col; i++)
        endstate *= 3;

    for (int i = 0; i < col; i++)
        Q[1][i] = grid[0][i] ? 2 : 1;
    memset(dp[0], -1, sizeof(dp[0]));
    dp[0][getstate(Q[1])] = 0;
        
    T1 = 1, T2 = 0;
    for (int i = 1; i < row; i++) {
        T1 ^= 1, T2 ^= 1;
        memset(dp[T2], -1, sizeof(dp[0]));
        for (int s = 0; s < endstate; s++) {
            if (dp[T1][s] == -1)
                continue;
            backstate(s, Q[0]);
            for (int j = 0; j < col; j++) {
                Q[1][j] = grid[i][j] ? 2 : Q[0][j]-1;
                if (Q[1][j] < 0) Q[1][j] = 0;
            }
            dfs(0, dp[T1][s], getstate(Q[1]));
        }
    }
    int ans = -1;
    for (int s = 0; s < endstate; s++)
        ans = max(ans, dp[T2][s]);
    return ans;
}

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        int tag;
        scanf("%d%d%d", &row, &col, &tag);
        memset(grid, false, sizeof(grid));
        for (int i = 0; i < tag; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            grid[x-1][y-1] = true;
        }
        printf("%d\n", solvedp());
    }
    return 0;
}