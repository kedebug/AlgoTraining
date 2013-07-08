
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int INFS = 0x3fffffff;
char s[MAXN];
int dp[MAXN][MAXN], choose[MAXN][MAXN];

void printstring(int i, int j) {
    if (i > j)
        return;

    if (i == j) {
        if (s[i] == '(' || s[i] == ')')
            printf("()");
        else
            printf("[]");
    } else if (choose[i][j] == -1) {
        printf("%c", s[i]);
        printstring(i + 1, j - 1);
        printf("%c", s[j]);
    } else {
        printstring(i, choose[i][j]);
        printstring(choose[i][j] + 1, j);
    }
}

int main() {
    while (gets(s)) {
        int len = strlen(s);
        for (int i = 0; i < len; i++)
            dp[i][i] = 1, dp[i+1][i] = 0;

        for (int p = 1; p < len; p++) {
            for (int i = 0, j = i + p; j < len; i++, j++) {
                dp[i][j] = INFS;
                choose[i][j] = -1;

                if ((s[i] == '(' && s[j] == ')') ||
                    (s[i] == '[' && s[j] == ']'))
                    dp[i][j] = min(dp[i][j], dp[i+1][j-1]);
                
                for (int k = i; k < j; k++) {
                    if (dp[i][j] > dp[i][k] + dp[k+1][j]) {
                        choose[i][j] = k;
                        dp[i][j] = dp[i][k] + dp[k+1][j];
                    }
                }
            }
        }
        printstring(0, len - 1);
        printf("\n");
    }
    return 0;
}