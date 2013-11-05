
#include <iostream>
#include <algorithm>
using namespace std;

const int INFS = 0x3fffffff;
const int MAXC = 81 * 4;
const int MAXR = 81 * 9;
const int MAXN = MAXC * MAXR + 10;

int U[MAXN], D[MAXN], L[MAXN], R[MAXN];
int grid[MAXR+10][MAXC+10], col[MAXN], row[MAXN], S[MAXC+10], Q[MAXR+10], QC;



void remove(int c) {
    L[R[c]] = L[c];
    R[L[c]] = R[c];
    for (int i = D[c]; i != c; i = D[i]) {
        for (int j = R[i]; j != i; j = R[j]) {
            U[D[j]] = U[j];
            D[U[j]] = D[j];
            S[col[j]] -= 1;
        }
    }
}

void resume(int c) {
    for (int i = U[c]; i != c; i = U[i]) {
        for (int j = L[i]; j != i; j = L[j]) {
            U[D[j]] = D[U[j]] = j;
            S[col[j]] += 1;
        }
    }
    R[L[c]] = L[R[c]] = c;
}

bool dfs() {
    if (R[0] == 0)
        return true;

    int mins = INFS, c = 0;
    for (int i = R[0]; i != 0; i = R[i]) {
        if (S[i] < mins)
            mins = S[i], c = i;
    }
    remove(c);
    for (int i = D[c]; i != c; i = D[i]) {
        for (int j = R[i]; j != i; j = R[j])
            remove(col[j]);
        Q[QC++] = row[i];
        if (dfs())
            return true;
        QC -= 1;
        for (int j = L[i]; j != i; j = L[j])
            resume(col[j]);
    }
    resume(c);
    return false;
}

void solve(int ans[]) {
    QC = 0;
    dfs();
    for (int i = 0; i < QC; i++)
        ans[(Q[i]-1)/9] = (Q[i] - 1) % 9 + 1;
}

void buildmatrix(char data[]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (data[i*9+j] == '.') {
                for (int k = 1; k <= 9; k++) {
                    int r = (i * 9 + j) * 9 + k;
                    int c1 = 81 * 0 + i * 9 + k;
                    int c2 = 81 * 1 + j * 9 + k;
                    int c3 = 81 * 2 + (i / 3 * 3 + j / 3) * 9 + k;
                    int c4 = 81 * 3 + i * 9 + j + 1;
                    grid[r][c1] = grid[r][c2] = grid[r][c3] = grid[r][c4] = 1;
                }
            } else {
                int k = data[i*9+j] - '0';
                int r = (i * 9 + j) * 9 + k;
                int c1 = 81 * 0 + i * 9 + k;
                int c2 = 81 * 1 + j * 9 + k;
                int c3 = 81 * 2 + (i / 3 * 3 + j / 3) * 9 + k;
                int c4 = 81 * 3 + i * 9 + j + 1;
                grid[r][c1] = grid[r][c2] = grid[r][c3] = grid[r][c4] = 1;
            }
        }
    }
}

void builddlx() {
    memset(S, 0, sizeof(S));
    for (int i = 1; i <= MAXC; i++) 
        R[i-1] = L[i+1] = U[i] = D[i] = i;
    R[MAXC] = L[1] = 0;

    int c = MAXC;
    for (int i = 1; i <= MAXR; i++) {
        int cflag = -1;
        for (int j = 1; j <= MAXC; j++) {
            if (grid[i][j] == 1) {
                c += 1;
                S[j] += 1;

                row[c] = i;
                col[c] = j;
                U[c] = U[j];
                D[c] = j;
                D[U[j]] = c;
                U[j] = c;

                if (cflag == -1) {
                    R[c] = L[c] = c;
                    cflag = c;
                } else {
                    L[c] = L[cflag];
                    R[c] = cflag;
                    R[L[c]] = c;
                    L[cflag] = c;
                }
            }
        }
    }
}

bool initdata() {
    char data[100];
    scanf("%s", data);

    if (data[0] == 'e')
        return false;

    memset(grid, 0, sizeof(grid));
    buildmatrix(data);
    builddlx();
    return true;
}

int main() {
    while (initdata()) {
        int ans[100];
        solve(ans);
        for (int i = 0; i < 81; i++)
            printf("%d", ans[i]);
        printf("\n");
    }
    return 0;
}