
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 10010;
int sumf[MAXN], sumt[MAXN], Q[MAXN], N, S, dp[MAXN];

inline double slope(int i, int j) {
    return 1.0 * (dp[i]-dp[j]) / (sumt[i]-sumt[j]);
}

void workout() {
    int s = 0, e = -1;
    dp[N] = 0; Q[++e] = N;
    for (int i = N-1; i >= 0; i--) {
        while (s < e && slope(Q[s], Q[s+1]) <= (double)sumf[i])
            ++s;
        int j = Q[s];
        dp[i] = dp[j] - sumf[i]*sumt[j] + (S+sumt[i])*sumf[i];
        while (s < e && slope(Q[e], i) <= slope(Q[e], Q[e-1]))
            --e;
        Q[++e] = i;
    }
}

int main() {
    while (~scanf("%d", &N)) {
        scanf("%d", &S);
        for (int i = 0; i < N; i++)
            scanf("%d%d", &sumt[i], &sumf[i]);
        sumt[N] = sumf[N] = 0;
        for (int i = N-1; i >= 0; i--) {
            sumt[i] += sumt[i+1];
            sumf[i] += sumf[i+1];
        }
        workout();
        printf("%d\n", dp[0]);
    }
    return 0;
}