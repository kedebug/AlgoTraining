
#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

const int INFS = 0x3fffffff;
const int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
char grid[25][25];
int col, row, dis[15][15];
bool vis[25][25];

struct Dirty {
    int x, y;
} dirty[20] ;

struct ST {
    int x, y, step;
    ST(int _x, int _y, int _step) : x(_x), y(_y), step(_step) {}
};

bool judge(int x, int y) {
    if (0 < x && x <= row && 0 < y && y <= col && grid[x][y] != 'x') {
        return true;
    }
    return false;
}

int bfs(const Dirty& src, const Dirty& dst) {
    deque<ST> Q;
    Q.push_back(ST(src.x, src.y, 0));
    memset(vis, false, sizeof(vis));
    vis[src.x][src.y] = true;

    while (!Q.empty()) {
        ST u = Q.front();
        Q.pop_front();

        if (u.x == dst.x && u.y == dst.y)
            return u.step;

        for (int i = 0; i < 4; i++) {
            int x = u.x + dir[i][0];
            int y = u.y + dir[i][1];
            if (judge(x, y) && !vis[x][y]) {
                vis[x][y] = true;
                Q.push_back(ST(x, y, u.step + 1));
            }
        }
    }
    return -1;
}

int dp[12][1<<12];
int dirtycnt;

inline int getflag(int r) {
    return 1 << r;
}

int dfs(int state, int u) {
    if (dp[u][state] != INFS)
        return dp[u][state];

    int s = state ^ getflag(u - 1);
    if (s == 0) 
        return dis[0][u];

    for (int i = 1; i <= dirtycnt; i++) {
        if (s & getflag(i-1)) {
            dp[u][state] = min(dp[u][state], dfs(s, i) + dis[i][u]);
        }
    }
    return dp[u][state];
}

int main() {
    while (scanf("%d%d", &col, &row) && col && row) {
        memset(dirty, 0, sizeof(dirty));
        dirtycnt = 0;
        for (int i = 1; i <= row; i++) { 
            scanf("%s", &grid[i][1]);
            for (int j = 1; j <= col; j++) {
                if (grid[i][j] == '*') {
                    dirtycnt += 1;
                    dirty[dirtycnt].x = i;
                    dirty[dirtycnt].y = j;
                } else if (grid[i][j] == 'o') {
                    dirty[0].x = i; dirty[0].y = j;
                }
            }
        }

        bool flag = false;
        for (int i = 0; i <= dirtycnt; i++) {
            for (int j = i; j <= dirtycnt; j++) {
                if (i == j) {
                    dis[i][j] = 0;
                } else {
                    dis[j][i] = dis[i][j] = bfs(dirty[i], dirty[j]);
                    if (dis[i][j] == -1) {
                        flag = true; break; 
                    }
                }
            }
        }
        if (flag) {
            printf("-1\n"); continue;
        }

        int ends = getflag(dirtycnt) - 1;
        for (int i = 0; i <= dirtycnt; i++) {
            for (int j = 0; j <= ends; j++)
                dp[i][j] = INFS;
        }
        dp[0][0] = 0;
        int ans = INFS;
        for (int i = 1; i <= dirtycnt; i++)
            ans = min(ans, dfs(ends, i));
        printf("%d\n", ans);
    }
    return 0;
}
