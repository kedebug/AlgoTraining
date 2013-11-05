
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;
int n, m, seq[MAXN];

int binarysearch(int low, int high) {
    while (low <= high) {
        int mid = (low + high) / 2;
        int count = 1, sum = 0;
        for (int i = 0; i < n; i++) {
            if (sum + seq[i] <= mid)
                sum += seq[i];
            else 
                sum = seq[i], count += 1;
        }
        if (count > m)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        int maxnum = 0, sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &seq[i]);
            sum += seq[i];
            maxnum = max(maxnum, seq[i]);
        }
        printf("%d\n", binarysearch(maxnum, sum));
    }
    return 0;
}