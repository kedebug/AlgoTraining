
#include <iostream>
#include <algorithm>
using namespace std;

const int INFS = 0x7fffffff;

int N, C, E, bound;
__int64 square[100], base[6][6];
bool succ;

inline __int64 getflag(int i) {
    return ((__int64)1 << (i - 1));
}

inline int geth(int i, int j) {
    return (2 * N + 1) * (i - 1) + j;
}

inline int getv(int i, int j) {
    return (2 * N + 1) * (i - 1) + j + N;
}

void build(void) {
    C = 0;
    memset(base, 0, sizeof(base));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            base[i][j] |= getflag(geth(i, j)) | getflag(geth(i + 1, j));
            base[i][j] |= getflag(getv(i, j)) | getflag(getv(i, j + 1));
            square[C++] = base[i][j];
        }
    }
    for (int size = 2; size <= N; size++) {
        for (int i = 1; i + size - 1 <= N; i++) {
            for (int j = 1; j + size - 1 <= N; j++) {
                square[C] = 0;
                for (int a = 0; a < size; a++) {
                    for (int b = 0; b < size; b++)
                        square[C] ^= base[i+a][j+b];
                }
                C += 1;
            }
        }
    }
}

int dfs(__int64 state, int depth) {
    int h = 0;
    __int64 u = 0, s = state;
    for (int i = 0; i < C; i++) {
        if ((s & square[i]) == square[i]) {
            h += 1;
            s ^= square[i];
            if (u == 0)
                u = square[i];
        }
    }
    if (h == 0) {
        succ = true;
        return depth;
    }
    if (depth + h > bound) {
        return depth + h;
    }

    int newbound = INFS;
    for (int i = 1; i <= E; i++) {
        if (u & getflag(i)) {
            int b = dfs(state ^ getflag(i), depth + 1);
            if (succ)
                return b;
            newbound = min(b, newbound);
        }
    }
    return newbound;
}

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        scanf("%d", &N);
        build();

        E = 2 * N * (N + 1);
        int k;
        __int64 state = ((__int64)1 << E) - 1;

        scanf("%d", &k);
        for (int i = 0; i < k; i++) {
            int x;
            scanf("%d", &x);
            state ^= getflag(x);
        }
        
        succ = false;
        bound = 0;
        while (!succ)
            bound = dfs(state, 0);

        printf("%d\n", bound);
    }
    return 0;
}
