
#include <iostream>
#include <algorithm>
using namespace std;

int row, col;
int state[60], statecnt, men[60], mapstate[110];
bool grid[110][12];
int dp[2][60][60];

bool judge(int s) {
    if (s & (s<<1))
        return false;
    if (s & (s<<2))
        return false;
    return true;
}

int calcmen(int s) {
    int ans = 0;
    while (s) {
        ans += 1;
        s &= (s-1);
    }
    return ans;
}

void initstate(int endstate) {
    statecnt = 0;
    for (int s = 0; s < endstate; s++) {
        if (judge(s)) {
            state[statecnt] = s;
            men[statecnt] = calcmen(s);
            statecnt += 1;
        }
    }
}

int solvedp() {
    memset(dp[0], -1, sizeof(dp[0]));
    for (int i = 0; i < statecnt; i++) {
        if (mapstate[0] & state[i])
            continue;
        dp[0][i][0] = men[i];
    }
    int T1 = 1, T2 = 0;
    for (int r = 1; r < row; r++) {
        T1 ^= 1, T2 ^= 1;
        memset(dp[T2], -1, sizeof(dp[0]));
        for (int i = 0; i < statecnt; i++) {
            if (state[i] & mapstate[r]) 
                continue;
            for (int j = 0; j < statecnt; j++) {
                if ((state[i] & state[j]) || (state[j] & mapstate[r-1]))
                    continue;
                for (int k = 0; k < statecnt; k++) {
                    if ((state[i] & state[k]) || (state[k] & state[j]))
                        continue;
                    if (dp[T1][j][k] != -1)
                        dp[T2][i][j] = max(dp[T2][i][j], dp[T1][j][k]+men[i]);
                }
            }
        }
    }
    int ans = -1;
    for (int i = 0; i < statecnt; i++)
        for (int j = 0; j < statecnt; j++)
            ans = max(ans, dp[T2][i][j]);
    return ans;
}

int main() {
    scanf("%d%d", &row, &col);
    for (int i = 0; i < row; i++) {
        char s[20];
        scanf("%s", s);
        mapstate[i] = 0;
        for (int j = 0; j < col; j++) {
            mapstate[i] <<= 1;
            mapstate[i] |= s[j] == 'H' ? 1 : 0;
        }
    }
    initstate(1<<col);
    printf("%d\n", solvedp());
    return 0;
}