// you can use includes, for example:
// #include <algorithm>
#include <vector>
#include <map>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(vector<int> &A) {
    // write your code in C++11
    int n = A.size();
    int sum = 0;
    map<int, int> count;
    for (int i = 0; i < n; i++) {
        if (A[i] < 0) {
            A[i] = -A[i];
        }
        sum += A[i];
        count[A[i]]++;
    }
    int V = sum / 2;
    vector<int> dp(V + 1, -1);
    dp[0] = 0;
    for (auto iter = count.begin(); iter != count.end(); iter++) {
        int a = iter->first;
        int c = iter->second;
        for (int v = 0; v <= V; v++) {
            if (dp[v] >= 0) {
                dp[v] = c;
            } else if (v >= a && dp[v-a] > 0) {
                dp[v] = dp[v-a] - 1;
            }
        }
    }
    for (int v = V; v >= 0; v--) {
        if (dp[v] != -1) {
            return abs(2 * v - sum);
        }
    }
    return -1;
}
