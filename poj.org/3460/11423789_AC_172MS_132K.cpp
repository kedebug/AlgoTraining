
#include <iostream>
#include <algorithm>
using namespace std;

int books[20], N;

void swapbooks(int p, int x, int q) {
    int buffer[20], c = 0;
    for (int i = x + 1; i <= q; i++)
        buffer[c++] = books[i];
    for (int i = p; i <= x; i++)
        buffer[c++] = books[i];
    for (int i = p; i <= q; i++)
        books[i] = buffer[i-p];
}

int getdiff() {
    int h = 0;
    for (int i = 0; i < N - 1; i++) {
        if (books[i] + 1 != books[i+1])
            h += 1;
    }
    if (books[N-1] != N)
        h += 1;
    return (h + 2) / 3;
}

int maxdepth;
bool succ;

int dfs(int depth) {
    int h = getdiff();
    if (h == 0) {
        succ = true;
        return depth;
    }
    int f = depth + h;
    if (f > maxdepth)
        return f;

    int newbound = 1e9;
    for (int p = 1; p < N; p++) {
        for (int i = 0, j = i + p; j < N; i++, j++) {
            for (int k = i; k < j; k++) {
                swapbooks(i, k, j);
                int f = dfs(depth + 1);
                if (succ)
                    return f;
                newbound = min(f, newbound);
                swapbooks(i, i + j - k - 1, j);
            }
        }
    }
    return newbound;
}

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++)
            scanf("%d", &books[i]);

        maxdepth = getdiff();
        if (maxdepth)
            succ = false;
        else
            succ = true;
        while (!succ && maxdepth < 5) 
            maxdepth = dfs(0);

        if (!succ)
            printf("5 or more\n");
        else
            printf("%d\n", maxdepth);
    }
    return 0;
}