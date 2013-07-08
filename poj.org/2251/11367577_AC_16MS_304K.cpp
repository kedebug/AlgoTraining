
#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

const int MAXN = 35;
const int dir[6][3] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};  
char gird[MAXN][MAXN][MAXN];
int L, R, C;
bool vis[MAXN][MAXN][MAXN];

struct ST {
    int x, y, z, step;
    ST(int _x, int _y, int _z, int _step) : x(_x), y(_y), z(_z), step(_step) {} 
};

bool judge(int x, int y, int z) {
    if (gird[z][x][y] != '#' && 
        0 < x && x <= R && 0 < y && y <= C && 0 < z && z <= L) {
        return true;
    }
    return false;
}

int bfs(int x, int y, int z) {
    deque<ST> Q;
    Q.push_back(ST(x, y, z, 0));
    vis[z][x][y] = true;

    while (!Q.empty()) {
        ST s = Q.front();
        Q.pop_front();

        if (gird[s.z][s.x][s.y] == 'E') 
            return s.step;

        for (int i = 0; i < 6; i++) {
            int a = s.x + dir[i][0];
            int b = s.y + dir[i][1];
            int c = s.z + dir[i][2];

            if (judge(a, b, c) && !vis[c][a][b]) {
                vis[c][a][b] = true;
                Q.push_back(ST(a, b, c, s.step + 1));
            }
        }
    }
    return -1;
}

int main() {
    while (scanf("%d%d%d", &L, &R, &C) && L && R && C) {
        int x, y, z;
        for (int i = 1; i <= L; i++) {
            for (int j = 1; j <= R; j++) {
                scanf("%s", &gird[i][j][1]);

                for (int k = 1; k <= C; k++) {
                    if (gird[i][j][k] == 'S')
                        x = j, y = k, z = i;
                }
            }
        }
        memset(vis, false, sizeof(vis));
        int ans = bfs(x, y, z);
        if (ans != -1)
            printf("Escaped in %d minute(s).\n", ans);
        else
            printf("Trapped!\n");
    }
    return 0;
}