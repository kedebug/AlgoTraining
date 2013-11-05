
#include <iostream>
#include <algorithm>
using namespace std;

const int dir[8][7] = {
    0,2,6,11,15,20,22,
    1,3,8,12,17,21,23,
    10,9,8,7,6,5,4,
    19,18,17,16,15,14,13,
    23,21,17,12,8,3,1,
    22,20,15,11,6,2,0,
    13,14,15,16,17,18,19,
    4,5,6,7,8,9,10};

const int aim[8] = {6,7,8,11,12,15,16,17};
const int rev[8] = {5,4,7,6,1,0,3,2};
int square[30], Q[30], qc;

void change(int r) {
    int t0 = square[dir[r][0]];
    for (int i = 0; i < 6; i++)
        square[dir[r][i]] = square[dir[r][i+1]];
    square[dir[r][6]] = t0;
}

int getremainder() {
    int a = 0, b = 0, c = 0;
    for (int i = 0; i < 8; i++) {
        if (square[aim[i]] == 1) a += 1;
        else if (square[aim[i]] == 2) b += 1;
        else if (square[aim[i]] == 3) c += 1;
    }
    int t = max(a, max(b, c));
    return 8 - t;
}

int bound;
bool succ;

int dfs(int step) {
    if (succ)
        return step;

    int h = getremainder();
    if (h == 0) {
        succ = true;
        return step;
    }
    if (step + h > bound)
        return step + h;

    int newbound = 1e9;
    for (int i = 0; i < 8; i++) {
        change(i);
        Q[qc++] = i;
        int f = dfs(step + 1);
        if (succ)
            return f;
        newbound = min(f, newbound);

        qc -= 1;
        change(rev[i]);
    }
    return newbound;
}

int main() {
    while (scanf("%d", &square[0]) && square[0]) {
        for (int i = 1; i < 24; i++)
            scanf("%d", &square[i]);

        if (!getremainder()) {
            printf("No moves needed\n%d\n", square[aim[0]]);
            continue;
        }
        qc = bound = 0;
        succ = false;
        while (!succ) {
            bound = dfs(0);
        }
        for (int i = 0; i < qc; i++)
            printf("%c", Q[i] + 'A');
        printf("\n%d\n", square[aim[0]]);
    }
    return 0;
}