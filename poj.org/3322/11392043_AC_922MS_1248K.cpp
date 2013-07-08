
#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

struct ST {
    int x, y;           // x, y 代表右下角的坐标位置
    int step, state;    // state = 0 竖立, state = 1 水平, state = 2 竖直
    ST() {}
    ST(int _x, int _y, int _step, int _state) 
        : x(_x), y(_y), step(_step), state(_state) {}
};

const int dir[3][4][3] = 
    {{{2,0,2},{-1,0,2},{0,-1,1},{0,2,1}},
    {{0,-2,0},{0,1,0},{-1,0,1},{1,0,1}}, 
    {{-2,0,0},{1,0,0},{0,1,2},{0,-1,2}}};

char grid[510][510];
bool vis[510][510][3];
int row, col;

bool judge(int x, int y, int state) {
    if (0 < x && x <= row && 0 < y && y <= col && grid[x][y] != '#') {
        if (state == 0 && grid[x][y] != 'E') {
            return true;
        }
        if (state == 1 && 1 < y && grid[x][y-1] != '#') {
            return true;
        }
        if (state == 2 && 1 < x && grid[x-1][y] != '#') {
            return true;
        }
    }
    return false;
}

int bfs(const ST& src, const ST& dst) {
    deque<ST> Q;
    Q.push_back(src);
    vis[src.x][src.y][src.state] = true;

    while (!Q.empty()) {
        ST u = Q.front();
        Q.pop_front();

        if (u.x == dst.x && u.y == dst.y && u.state == dst.state)
            return u.step;

        for (int i = 0; i < 4; i++) {
            int x = u.x + dir[u.state][i][0];
            int y = u.y + dir[u.state][i][1];
            int state = dir[u.state][i][2];
            if (!vis[x][y][state] && judge(x, y, state)) {
                vis[x][y][state] = true;
                Q.push_back(ST(x, y, u.step + 1, state));
            }
        }
    }
    return -1;
}

int main() {
    while (scanf("%d%d", &row, &col) && row && col) {
        ST src, dst;
        bool cflag = false;
        for (int i = 1; i <= row; i++) {
            scanf("%s", &grid[i][1]);
            for (int j = 1; j <= col; j++) {
                if (grid[i][j] == 'O') {
                    dst.x = i, dst.y = j, dst.state = 0;
                } else if (grid[i][j] == 'X') {
                    if (!cflag) {
                        cflag = true;
                        src.x = i, src.y = j, src.state = 0;
                    } else {
                        if (src.x == i) {
                            src.y = max(src.y, j);
                            src.state = 1;
                        } else if (src.y == j) {
                            src.x = max(src.x, i);
                            src.state = 2;
                        }
                    }
                }
                vis[i][j][0] = vis[i][j][1] = vis[i][j][2] = false;
            }
        }
        src.step = 0;
        int ans = bfs(src, dst);
        if (ans == -1) 
            printf("Impossible\n");
        else
            printf("%d\n", ans);
    }
    return 0;
}