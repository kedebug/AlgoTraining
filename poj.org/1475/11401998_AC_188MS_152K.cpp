
#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

const int dir[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};
const char dirman[4] = {'n','s','e','w'};
const char dirbox[4] = {'N','S','E','W'};

char grid[21][21];
int row, col;

struct ST {
    int manx, many;
    int boxx, boxy;
    string path;
    ST() : path("") {}
    ST(int _manx, int _many, int _boxx, int _boxy, string& _path) 
        : manx(_manx), many(_many), boxx(_boxx), boxy(_boxy), path(_path) {}
};

struct POS {
    int x, y;
    string path;
    POS() : path("") {}
    POS(int _x, int _y) : x(_x), y(_y), path("") {}
    POS(int _x, int _y, string& _path) : x(_x), y(_y), path(_path) {}
};

bool judge(int x, int y) {
    if (0 < x && x <= row && 0 < y && y <= col && grid[x][y] != '#') {
        return true;
    }
    return false;
}

bool bfsman(string& path, const POS& s, const POS& t) {
    bool vis[21][21];
    memset(vis, false, sizeof(vis));
    queue<POS> Q;
    Q.push(s);
    vis[s.x][s.y] = true;

    while (!Q.empty()) {
        POS u = Q.front();
        Q.pop();

        if (u.x == t.x && u.y == t.y) {
            path = u.path;  
            return true;
        }
        for (int i = 0; i < 4; i++) {
            int x = u.x + dir[i][0];
            int y = u.y + dir[i][1];
            string p = u.path + dirman[i];

            if (!vis[x][y] && judge(x, y)) {
                vis[x][y] = true;
                Q.push(POS(x, y, p));
            }
        }
    }
    return false;
}

bool bfsbox(string& path, const ST& s, const POS& t) {
    bool vis[21][21];
    memset(vis, false, sizeof(vis));
    queue<ST> Q;
    Q.push(s);
    vis[s.boxx][s.boxy] = true;

    while (!Q.empty()) {
        ST u = Q.front();
        Q.pop();

        if (u.boxx == t.x && u.boxy == t.y) {
            path = u.path;
            return true;
        }

        grid[u.boxx][u.boxy] = '#';
        for (int i = 0; i < 4; i++) {
            int x = u.boxx + dir[i][0];
            int y = u.boxy + dir[i][1];
            int a = u.boxx - dir[i][0];
            int b = u.boxy - dir[i][1];
            if (!vis[x][y] && judge(x, y) && judge(a, b)) {
                string pathman = "";
                if (bfsman(pathman, POS(u.manx, u.many), POS(a, b))) {
                    vis[x][y] = true;
                    string p = u.path + pathman + dirbox[i];
                    Q.push(ST(u.boxx, u.boxy, x, y, p));
                }
            }
        }
        grid[u.boxx][u.boxy] = '.';
    }
    return false;
}

int main() {
    int cases = 0;
    while (scanf("%d%d", &row, &col) && row && col) {
        ST s;
        POS t;
        for (int i = 1; i <= row; i++) {
            scanf("%s", &grid[i][1]);
            for (int j = 1; j <= col; j++) {
                if (grid[i][j] == 'S') 
                    s.manx = i, s.many = j;
                else if (grid[i][j] == 'B')
                    s.boxx = i, s.boxy = j;
                else if (grid[i][j] == 'T')
                    t.x = i, t.y = j;
            }
        }
        string path = "";
        if (bfsbox(path, s, t))
            printf("Maze #%d\n%s\n\n", ++cases, path.c_str());
        else
            printf("Maze #%d\nImpossible.\n\n", ++cases);
    }
    return 0;
}