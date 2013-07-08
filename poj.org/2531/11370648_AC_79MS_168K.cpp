
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 30;
int map[MAXN][MAXN], QA[MAXN], QB[MAXN];
int N, ans;

void dfs(int k, int val, int a, int b) {
    if (ans < val)
        return ;

    int sum = 0;
    for (int i = 0; i < a; i++)
        sum += map[QA[i]][k];

    if (k == N) {
        ans = min(ans, sum + val);
    } else {
        QA[a] = k;
        dfs(k + 1, sum + val, a + 1, b);
    }

    sum = 0;
    for (int i = 0; i < b; i++)
        sum += map[QB[i]][k];

    if (k == N) {
        ans = min(ans, sum + val);
    } else {
        QB[b] = k;
        dfs(k + 1, sum + val, a, b + 1);
    }
}

int main() {
    int sum = 0;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", &map[i][j]);
            sum += map[i][j];
        }
    }
    ans = 0x3fffffff;
    dfs(1, 0, 0, 0);
    printf("%d\n", sum / 2 - ans);
    return 0;
}
