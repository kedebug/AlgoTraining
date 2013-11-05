
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int INFS = 0x3FFFFFFF;
int square[10][10][10][10], grid[10][10];
int dp[10][10][10][10][16];

void initsquare() {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            for (int p = i; p <= 8; p++) {
                for (int q = j; q <= 8; q++) {
                    int t = 0;
                    for (int x = i; x <= p; x++)
                        for (int y = j; y <= q; y++)
                            t += grid[x][y];
                    square[i][j][p][q] = t * t;
                }
            }
        }
    }
}

int solvedp(int k, int x, int y, int ex, int ey) {
    if (k == 1)
        return square[x][y][ex][ey];

    if (dp[x][y][ex][ey][k] != -1)
        return dp[x][y][ex][ey][k];

    int ans = INFS;
    for (int i = x; i < ex; i++) {
        ans = min(ans, square[x][y][i][ey] + solvedp(k-1, i+1, y, ex, ey));
        ans = min(ans, square[i+1][y][ex][ey] + solvedp(k-1, x, y, i, ey));
    } 
    for (int i = y; i < ey; i++) {
        ans = min(ans, square[x][y][ex][i] + solvedp(k-1, x, i+1, ex, ey));
        ans = min(ans, square[x][i+1][ex][ey] + solvedp(k-1, x, y, ex, i));
    }
    return dp[x][y][ex][ey][k] = ans;
}

int main() {
    int n;
    scanf("%d", &n);

    double ave = 0;
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            scanf("%d", &grid[i][j]);
            ave += grid[i][j];
        }
    }
    initsquare();
    memset(dp, -1, sizeof(dp));
    double ans = solvedp(n, 1, 1, 8, 8);
    ave /= n;
    ans /= n;
    ans -= ave * ave;
    printf("%.3lf\n", sqrt(ans));
    return 0;
}