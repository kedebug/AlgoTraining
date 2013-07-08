
#include <iostream>
#include <algorithm>
using namespace std;

const int INFS = 0x3FFFFFFF;

struct POINT {
    int x1, y1, x2, y2;
    int color;
} rect[20] ;

int up[20], dp[15][1<<15];

bool judge(int i, int j) {
    // whether j is upper to i
    if (rect[j].x2 != rect[i].x1) return false;
    if (rect[j].y2 <= rect[i].y1) return false;
    if (rect[j].y1 >= rect[i].y2) return false;
    return true;
}

int workout(int n) {
    for (int i = 0; i < n; i++) {
        up[i] = 0;
        for (int j = 0; j < n; j++)
            if (judge(i, j)) up[i] |= (1<<j);
    }

    int ENDS = (1<<n) - 1;

    for (int i = 0; i < n; i++)
        for (int s = 0; s <= ENDS; s++)
            dp[i][s] = INFS;
    for (int i = 0; i < n; i++)
        if (up[i] == 0) dp[i][1<<i] = 1;

    for (int s = 0; s <= ENDS; s++) {
        for (int i = 0; i < n; i++) {
            if (s & (1<<i)) continue;
            if ((s & up[i]) != up[i]) continue;
            for (int j = 0; j < n; j++) {
                if (!(s & (1<<j))) continue;
                int now = s | (1<<i);
                int value = dp[j][s];
                if (rect[i].color != rect[j].color) value += 1;
                dp[i][now] = min(dp[i][now], value);
            }
        }
    }
    int ans = INFS;
    for (int i = 0; i < n; i++)
        ans = min(ans, dp[i][ENDS]);
    return ans;
}

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d%d%d%d%d", &rect[i].x1, &rect[i].y1, &rect[i].x2, &rect[i].y2, &rect[i].color);
        printf("%d\n", workout(n));
    }
    return 0;
}