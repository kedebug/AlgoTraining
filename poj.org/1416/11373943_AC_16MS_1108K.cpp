
#include <iostream>
#include <algorithm>
using namespace std;

char num[10], vis[1000000];
int QRES[10], QRC, Q[10], QC, L, N, Ans; 

void dfs(int k, int cur, int sum) {
    if (sum > N)
        return ;

    if (k == L) {
        if (sum == Ans) {
            vis[Ans] += 1;
        } else if (sum > Ans) {
            Ans = sum;
            vis[Ans] += 1;
            QRC = QC;
            for (int i = 0; i < QC; i++)
                QRES[i] = Q[i];
        }
    } else {
        Q[QC++] = 10 * cur + num[k];
        dfs(k + 1, 0, 10 * cur + num[k] + sum);
        QC -= 1;
        if (k + 1 < L) {
            dfs(k + 1, 10 * cur + num[k], sum);
        }
    }
}

int main() {
    while (scanf("%d%s", &N, num)) {
        if (N == 0 || num[0] == '0')
            break ;
        L = strlen(num);
        for (int i = 0; i < L; i++) 
            num[i] -= '0';

        QRC = QC = Ans = 0;
        memset(vis, 0, sizeof(vis));
        dfs(0, 0, 0);

        if (vis[Ans] == 1) {
            printf("%d %d", Ans, QRES[0]);
            for (int i = 1; i < QRC; i++)
                printf(" %d", QRES[i]);
            printf("\n");
        } else if (vis[Ans] > 1) {
            printf("rejected\n");
        } else if (vis[Ans] == 0) {
            printf("error\n");
        }
    }
    return 0;
}
