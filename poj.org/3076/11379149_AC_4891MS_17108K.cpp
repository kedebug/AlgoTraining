
#include <iostream>
#include <algorithm>
using namespace std;

const int INFS = 0x3fffffff;
const int MAXC = 16 * 16 * 4;
const int MAXR = 16 * 16 * 16;
const int MAXN = MAXC * MAXR + 10;

int U[MAXN], D[MAXN], L[MAXN], R[MAXN];
int grid[MAXR+10][MAXC+10], col[MAXN], row[MAXN], S[MAXC+10], Q[MAXR+10], QC;
char data[20][20];

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

void solve(char ans[]) {
    QC = 0;
    dfs();
    for (int i = 0; i < QC; i++)
        ans[(Q[i]-1)/16] = (Q[i] - 1) % 16 + 'A';
}

void buildmatrix() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (data[i][j] == '-') {
                for (int k = 1; k <= 16; k++) {
                    int r = (i * 16 + j) * 16 + k;
                    int c1 = 256 * 0 + i * 16 + k;
                    int c2 = 256 * 1 + j * 16 + k;
                    int c3 = 256 * 2 + (i / 4 * 4 + j / 4) * 16 + k;
                    int c4 = 256 * 3 + i * 16 + j + 1;
                    grid[r][c1] = grid[r][c2] = grid[r][c3] = grid[r][c4] = 1;
                }
            } else {
                int k = data[i][j] - 'A' + 1;
                int r = (i * 16 + j) * 16 + k;
                int c1 = 256 * 0 + i * 16 + k;
                int c2 = 256 * 1 + j * 16 + k;
                int c3 = 256 * 2 + (i / 4 * 4 + j / 4) * 16 + k;
                int c4 = 256 * 3 + i * 16 + j + 1;
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
    while (scanf("%s", data[0]) != EOF)
    {
        for (int i = 1; i < 16; i++)
            scanf("%s", data[i]);

        memset(grid, 0, sizeof(grid));
        buildmatrix();
        builddlx();
        return true ;
    }
    return false;
}

int main() {
    while (initdata()) {
        char ans[300];
        solve(ans);
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                printf("%c", ans[i*16+j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}