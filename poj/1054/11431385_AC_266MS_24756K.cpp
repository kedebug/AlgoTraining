
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 5010;

bool G[MAXN][MAXN];

struct POINT {
    int x, y;
    bool operator < (const POINT& other) {
        if (x == other.x)
            return y < other.y;
        return x < other.x;
    }
} P[MAXN];

int row, col, N;

bool judge(int x, int y) {
    if (0 < x && x <= row && 0 < y && y <= col) {
        return true;
    }
    return false;
}

int workout() {
    int ans = 2;
    for (int i = 0; i < N-1; i++) {
        for (int j = i+1; j < N; j++) {
            int dx = P[j].x - P[i].x;
            int dy = P[j].y - P[i].y;

            if (P[j].x + (ans-2)*dx > row)
                break;
            if (P[j].y + (ans-2)*dy > col || P[j].y + (ans-2)*dy < 1)
                continue;
            if (judge(P[i].x-dx, P[i].y-dy))
                continue;

            int t = 1;
            int x = P[j].x, y = P[j].y;
            while (judge(x, y) && G[x][y]) {
                x += dx, y += dy, t += 1;
            }
            if (!judge(x+dx, y+dy)) 
                ans = max(ans, t);
        }
    }
    return ans > 2 ? ans : 0;
}

int main() {
    while (~scanf("%d%d", &row, &col)) {
        scanf("%d", &N);
        memset(G, false, sizeof(G));
        for (int i = 0; i < N; i++) {
            scanf("%d%d", &P[i].x, &P[i].y);
            G[P[i].x][P[i].y] = true;
        }
        sort(P, P + N);
        printf("%d\n", workout());
    }
    return 0;
}