// you can use includes, for example:
// #include <algorithm>
#include <vector>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(string &S) {
    // write your code in C++11
    int n = S.size();
    if (n == 0) {
        return 0;
    }
    string s;
    s += "^";
    for (int i = 0; i < n; i++) {
        s += "#" + S.substr(i, 1);
    }
    s += "#$";
    n = s.size();
    vector<int> p(n, 0);
    int id = 0, mx = 0;
    for (int i = 1; i < n - 1; i++) {
        p[i] = mx > i ? min(mx - i, p[2*id-i]) : 1;
        while (s[i+p[i]] == s[i-p[i]]) {
            p[i]++;
        }
        if (i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
    }
    int sum = 0;
    for (int i = 1; i < n - 1; i++) {
        sum += (p[i] - 1) / 2;
        if (sum > 100000000) {
            return -1;
        }
    }
    return sum;
}
