
#include <iostream>
#include <algorithm>
using namespace std;


struct ST {
    int c00, c01;
    int c10, c11;
    ST() : c00(0), c01(0), c10(0), c11(0) {}
};

struct POS {
    int x, y;
    POS(int _x, int _y) : x(_x), y(_y) {}
};

const int dir[9][2] = {{0,0},{-1,0},{-2,0},{0,-1},
                  {0,-2},{1,0},{2,0},{0,1},{0,2}};
bool vis[370][9][7][7][7][7];
int day[370], N;

inline int getflag(int r) {
    return 1 << r;
}

bool judge(int k, const POS& u, const ST& s) {
    if (s.c00 == 7 || s.c01 == 7 || s.c10 == 7 || s.c11 == 7) 
        return false;

    int flag = 0;
    int x = u.x, y = u.y;
    flag |= getflag(4*x + y) | getflag(4*x + y+1);
    flag |= getflag(4*(x+1) + y) | getflag(4*(x+1) + y+1);
    if (flag & day[k])
        return false;

    if (vis[k][3*x+y][s.c00][s.c01][s.c10][s.c11])
        return false;
    vis[k][3*x+y][s.c00][s.c01][s.c10][s.c11] = true;
    return true;
}

bool dfs(int k, const POS& u, const ST& state) {
    if (k == N)
        return true;

    ST s = state;
    s.c00 += 1, s.c01 += 1;
    s.c10 += 1, s.c11 += 1;

    if (u.x == 0 && u.y == 0)
        s.c00 = 0;
    else if (u.x == 0 && u.y == 2)
        s.c01 = 0;
    else if (u.x == 2 && u.y == 0)
        s.c10 = 0;
    else if (u.x == 2 && u.y == 2)
        s.c11 = 0;

    if (!judge(k, u, s))
        return false;

    for (int i = 0; i < 9; i++) {
        int x = u.x + dir[i][0];
        int y = u.y + dir[i][1];
        if (0 <= x && x < 3 && 0 <= y && y < 3) {
            if (dfs(k + 1, POS(x, y), s))
                return true;
        }
    }
    return false;
}

int main() {
    while (scanf("%d", &N) && N) {
        for (int i = 0; i < N; i++) {
            day[i] = 0;
            for (int j = 0; j < 16; j++) {
                int x;
                scanf("%d", &x);
                day[i] <<= 1;
                day[i] |= x;
            }
            memset(vis[i], false, sizeof(vis[i]));
        }
        ST s;
        if (dfs(0, POS(1, 1), s))
            printf("1\n");
        else
            printf("0\n");
    }
    return 0;
}