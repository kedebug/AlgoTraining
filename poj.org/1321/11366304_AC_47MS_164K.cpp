
#include <iostream>
#include <algorithm>
using namespace std;

char grid[10][10];
int N, K, ans;

void dfs(int l, int k, int flag) {
    if (k == 0) {
        ans++;
        return ;
    }

    if (l > N)
        return ;

    dfs(l + 1, k, flag);

    for (int i = 1; i <= N; i++) {
        if (grid[l][i] == '#' && !(flag & (1<<i))) {
            dfs(l + 1, k - 1, flag | (1<<i));
        }
    }
}

int main() {
    while (scanf("%d%d", &N, &K)) {
        if (N == -1 && K == -1)
            break ;
        for (int i = 1; i <= N; i++)
            scanf("%s", &grid[i][1]);

        ans = 0;
        dfs(1, K, 0);
        printf("%d\n", ans);
    } 
}