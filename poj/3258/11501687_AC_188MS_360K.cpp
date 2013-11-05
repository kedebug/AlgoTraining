
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 50010;
int n, m, d[MAXN];

int binarysearch(int low, int high) {
    while (low <= high) {
        int mid = (low + high) / 2;
        int count = 0;
        int s = 0, e = 1;
        while (e < n) {
            if (d[e] - d[s] >= mid)
                s = e, e += 1;
            else 
                e += 1, count += 1;
        }
        if (count > m)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return high;
}

int main() {
    int len;
    while (~scanf("%d%d%d", &len, &n, &m)) {
        for (int i = 1; i <= n; i++)
            scanf("%d", &d[i]);
        d[0] = 0, d[n+1] = len;
        n += 2;
        sort(d, d + n);
        int mind = len;
        for (int i = 1; i < n; i++)
            mind = min(mind, d[i] - d[i-1]);
        printf("%d\n", binarysearch(mind, len));
    }
    return 0;
}