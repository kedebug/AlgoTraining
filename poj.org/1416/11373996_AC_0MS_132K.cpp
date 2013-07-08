
#include <iostream>
#include <algorithm>
using namespace std;

char num[10];
int QRES[10], QRC, Q[10], QC, L, N, Ans; 
bool flag, cflag;

void dfs(int k, int cur, int sum) {
    if (sum > N)
        return ;

    if (k == L) {
        if (sum == Ans) {
            cflag = true;
        } else if (sum > Ans) {
            flag = true;
            cflag = false;
            Ans = sum;;
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
        flag = cflag = false;
        dfs(0, 0, 0);

        if (flag && !cflag) {
            printf("%d %d", Ans, QRES[0]);
            for (int i = 1; i < QRC; i++)
                printf(" %d", QRES[i]);
            printf("\n");
        } else if (flag && cflag) {
            printf("rejected\n");
        } else {
            printf("error\n");
        }
    }
    return 0;
}
