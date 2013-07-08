
#include <iostream>
#include <algorithm> 
using namespace std;

struct ST {
    int arrive, interval, times;
    bool operator < (const ST& other) const { return times > other.times; }
} route[1800];

int N, hash[60], routecnt, ans;

bool checkroute(int s, int delta) {
    for (int i = s; i < 60; i += delta) {
        if (!hash[i]) 
            return false;
    }
    return true;
}

void dfs(int k, int sum) {
    if (sum >= ans)
        return;
    if (N == 0) {
        ans = min(ans, sum);
        return;
    }
    for (int i = k; i < routecnt; i++) { 
        if (route[i].times > N)
            continue;
        if (sum + N/route[i].times >= ans)
            return;
        if (!checkroute(route[i].arrive, route[i].interval))
            continue;

        for (int j = route[i].arrive; j < 60; j += route[i].interval)
            N -= 1, hash[j] -= 1;

        dfs(i, sum + 1);

        for (int j = route[i].arrive; j < 60; j += route[i].interval)
            N += 1, hash[j] += 1;
    }
}

int main() {
    scanf("%d", &N);
    memset(hash, 0, sizeof(hash));
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        hash[x] += 1;
    }
    routecnt = 0;
    for (int i = 0; i < 30; i++) {
        for (int j = i + 1; j + i < 60; j++) {
            if (checkroute(i, j)) {
                route[routecnt].arrive = i;
                route[routecnt].interval = j;
                route[routecnt].times = (59-i)/j + 1;
                routecnt += 1;
            }
        }
    }
    sort(route, route + routecnt);
    ans = 17;
    dfs(0, 0);
    printf("%d\n", ans);
    return 0;
}