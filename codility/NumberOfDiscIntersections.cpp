// you can use includes, for example:
#include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

struct seg {
    long long left;
    long long right;    
};

bool operator<(const seg& a, const seg& b) {
    if (a.left == b.left) {
        return a.right < b.right;
    }
    return a.left < b.left;
}

int search(vector<seg>& segs, long long bound, int l, int r) {
    while (l <= r) {
        int m = (l + r) / 2;
        if (segs[m].left <= bound) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return l;
}

int solution(vector<int> &A) {
    // write your code in C++11
    int n = A.size();
    vector<seg> segs(n);
    for (int i = 0; i < n; i++) {
        segs[i].left = (long long)i - (long long)A[i];
        segs[i].right = (long long)i + (long long)A[i];
    } 
    sort(segs.begin(), segs.end());
    int sum = 0;
    for (int i = 0; i < n - 1; i++) {
        int b = search(segs, segs[i].right, i + 1, n - 1);
        sum += b - i - 1;
        if (sum > 10000000) {
            return -1;
        }
    }
    return sum;
}
