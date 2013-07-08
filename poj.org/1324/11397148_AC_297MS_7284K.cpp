
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

bool vis[21][21][1<<14];
bool stone[21][21];
int row, col, L, K;

const int dir[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};

struct Body {
    int x, y;
} body[10];

struct ST {
    int x, y, step, state, f;
    ST(int _x, int _y, int _step, int _state, int _f) 
        : x(_x), y(_y), step(_step), state(_state), f(_f) {}
    bool operator < (const ST& other) const { return f > other.f; }
};

void setstone() {
    for (int i = 1; i < L; i++)
        stone[body[i].x][body[i].y] = true;
}

void clearstone() {
    for (int i = 1; i < L; i++)
        stone[body[i].x][body[i].y] = false;
}

int getstate(int x, int y) {
    int state = 0;
    for (int i = 1; i < L; i++) {
        state <<= 2;
        if (body[i].x > body[i-1].x)        // up
            state |= 0;     
        else if (body[i].x < body[i-1].x)   // down
            state |= 1;
        else if (body[i].y > body[i-1].y)   // left
            state |= 2;
        else if (body[i].y < body[i-1].y)   // right
            state |= 3;
    }
    return state;
}

void setbody(int x, int y, int state) {
    const int MASK = 3;
    body[0].x = x, body[0].y = y;
    for (int i = 1; i < L; i++) {
        int val = (state >> ((L-i-1)*2)) & MASK;
        body[i].x = body[i-1].x;
        body[i].y = body[i-1].y;
        if (val == 0) body[i].x += 1;
        else if (val == 1) body[i].x -= 1;
        else if (val == 2) body[i].y += 1;
        else if (val == 3) body[i].y -= 1;
    }
}

bool judge(int x, int y) {
    if (0 < x && x <= row && 0 < y && y <= col && !stone[x][y]) {
        return true;
    }
    return false;
}

inline int getdiff(int x, int y) {
    return abs(x - 1) + abs(y - 1);
}

int astar() {
    priority_queue<ST> Q;
    int x = body[0].x, y = body[0].y;
    int state = getstate(x, y);
    int f = getdiff(x, y);
    Q.push(ST(x, y, 0, state, f));
    vis[x][y][state] = true;

    while (!Q.empty()) {
        ST u = Q.top();
        Q.pop();

        if (u.x == 1 && u.y == 1)
            return u.step;

        setbody(u.x, u.y, u.state);
        setstone();
        for (int i = 0; i < 4; i++) {
            x = u.x + dir[i][0];
            y = u.y + dir[i][1];
            state = (L<2) ? 0 : (u.state>>2) | (i<<((L-2)*2));
            if (judge(x, y) && !vis[x][y][state]) {
                vis[x][y][state] = true;
                f = u.step + 1 + getdiff(x, y);
                Q.push(ST(x, y, u.step + 1, state, f));
            }
        }
        clearstone();
    }
    return -1;
}

int bfs() {
    bool visit[21][21];
    memset(visit, false, sizeof(visit));
    priority_queue<ST> Q;
    int x = body[0].x, y = body[0].y;
    int f = getdiff(x, y);
    Q.push(ST(x, y, 0, 0, f));
    visit[x][y] = true;

    while (!Q.empty()) {
        ST u = Q.top();
        Q.pop();

        if (u.x == 1 && u.y == 1)
            return u.step;

        for (int i = 0; i < 4; i++) {
            x = u.x + dir[i][0];
            y = u.y + dir[i][1];
            if (judge(x, y) && !visit[x][y]) {
                visit[x][y] = true;
                f = u.step + 1 + getdiff(x, y);
                Q.push(ST(x, y, u.step + 1, 0, f));
            } 
        }
    }
    return -1;
}

int main() {
    int cases = 0;
    while (scanf("%d%d%d", &row, &col, &L) && row && col && L) {
        for (int i = 0; i < L; i++)
            scanf("%d%d", &body[i].x, &body[i].y); 
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= col; j++) {
                stone[i][j] = false;
                memset(vis[i][j], false, sizeof(vis[0][0]));
            }
        }
        scanf("%d", &K);
        for (int i = 0; i < K; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            stone[x][y] = true;
        }
        int ans;
        int minstep = bfs();
        setstone();
        int maxstep = bfs();
        clearstone();

        if (minstep == -1) 
            ans = -1;
        else if (minstep == maxstep)
            ans = minstep;
        else
            ans = astar();

        printf("Case %d: %d\n", ++cases, ans);
    }
    return 0;
}