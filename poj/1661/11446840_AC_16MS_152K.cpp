
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1010;
const int INFS = 0x3fffffff;

struct BOARD {
    int x1, x2, h;
    bool operator < (const BOARD& other) const { return h < other.h; }
} board[MAXN];

int dp[MAXN][2];

int workout(int n, int maxh) {
    for (int i = 1; i < n; i++) {
        for (int j = i-1; j >= 0; j--) {
            if (board[i].x1 >= board[j].x1 && board[i].x1 <= board[j].x2) {
                int h = board[i].h - board[j].h;
                if (h > maxh) dp[i][0] = INFS;
                else if (j == 0) dp[i][0] = h;
                else dp[i][0] = min(dp[j][0] + board[i].x1 - board[j].x1, dp[j][1] + board[j].x2 - board[i].x1) + h;
                break;
            }
        }
        for (int j = i-1; j >= 0; j--) {
            if (board[i].x2 >= board[j].x1 && board[i].x2 <= board[j].x2) {
                int h = board[i].h - board[j].h;
                if (h > maxh) dp[i][1] = INFS;
                else if (j == 0) dp[i][1] = h;
                else dp[i][1] = min(dp[j][0] + board[i].x2 - board[j].x1, dp[j][1] + board[j].x2 - board[i].x2) + h;
                break;
            }
        }
    }
    return dp[n-1][1];
}

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        int n, x, y, maxh;
        scanf("%d%d%d%d", &n, &x, &y, &maxh);
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d", &board[i].x1, &board[i].x2, &board[i].h);
            if (board[i].x1 > board[i].x2) 
                swap(board[i].x1, board[i].x2);
        }
        board[0].x1 = board[0].x2 = x, board[0].h = y;
        board[n+1].x1 = -20010, board[n+1].x2 = 20010, board[n+1].h = 0;
        n += 2;
        sort(board, board + n);
        printf("%d\n", workout(n, maxh));
    }
    return 0;
}