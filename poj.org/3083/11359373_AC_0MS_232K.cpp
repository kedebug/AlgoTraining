
#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

const int MAXN = 50;

struct ST {
    int x, y, step;
    ST(int _x, int _y, int _s) : x(_x), y(_y), step(_s) {}
};

char grid[MAXN][MAXN];
bool vis[MAXN][MAXN];
int dir[4][2] = {{0,-1}, {-1,0}, {0,1}, {1,0}};
int ans;

bool lhsDfs(int x, int y, int o, int step) {
    if (grid[x][y] == 'E') {
        ans = step; 
        return true;
    }

    for (int i = o; i < o + 4; ++i) {
        int newx = x + dir[i%4][0];
        int newy = y + dir[i%4][1];

        if (grid[newx][newy] != '#') {
            vis[newx][newy] = true;
            if (lhsDfs(newx, newy, (i-1+4)%4, step+1))
                return true;
            vis[newx][newy] = false;
        }
    }
    return false;
}

bool rhsDfs(int x, int y, int o, int step) {
    if (grid[x][y] == 'E') {
        ans = step; 
        return true;
    }

    for (int i = o + 4; i > o; --i) {
        int newx = x + dir[i%4][0];
        int newy = y + dir[i%4][1];

        if (grid[newx][newy] != '#') {
            vis[newx][newy] = true;
            if (rhsDfs(newx, newy, (i+1)%4, step+1))
                return true;
            vis[newx][newy] = false;
        }
    }
    return false;
}

int bfs(int x, int y) {
    deque<ST> q;
    q.push_back(ST(x, y, 1));
    vis[x][y] = true;

    while (!q.empty()) {
        ST s = q.front();
        q.pop_front();

        if (grid[s.x][s.y] == 'E') 
            return s.step;

        for (int i = 0; i < 4; ++i) {
            int newx = s.x + dir[i][0];
            int newy = s.y + dir[i][1];

            if (grid[newx][newy] != '#' && !vis[newx][newy]) {
                vis[newx][newy] = true;
                q.push_back(ST(newx, newy, s.step + 1));   
            }
        }
    }
}

int main()
{
    int cases;
    scanf("%d", &cases);

    while (cases--) {
        int row, col;
        scanf("%d %d", &col, &row);

        memset(grid, '#', sizeof(grid));
        for (int i = 1; i <= row; ++i)
            scanf("%s", &grid[i][1]);

        int x, y;
        for (int i = 1; i <= row; ++i) 
            for (int j = 1; j <= col; ++j)
                if (grid[i][j] == 'S') x = i, y = j;

        memset(vis, false, sizeof(vis));
        vis[x][y] = true;
        lhsDfs(x, y, 0, 1);
        printf("%d ", ans);

        memset(vis, false, sizeof(vis));
        vis[x][y] = true;
        rhsDfs(x, y, 0, 1);
        printf("%d ", ans);

        memset(vis, false, sizeof(vis));
        printf("%d\n", bfs(x, y));
    }
    return 0;
}