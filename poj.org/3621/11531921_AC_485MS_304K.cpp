
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 1010;
const int INFS = 1e9;

struct edge {
    int to, cost;
    edge(int _to, int _cost) : to(_to), cost(_cost) {}
};

int fun[MAXN], times[MAXN];
double d[MAXN];
bool inq[MAXN];
vector<edge> G[MAXN];

bool SPFA(int s, int n, double delta) {
    for (int i = 1; i <= n; i++) 
        times[i] = 0, d[i] = INFS, inq[i] = false;
    queue<int> Q;
    Q.push(s);
    times[s] = 1, inq[s] = true, d[s] = 0.0;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        inq[u] = false;
        for (int i = 0; i < G[u].size(); i++) {
            edge& e = G[u][i];
            if (d[e.to] > d[u] + delta*e.cost - fun[e.to]) {
                d[e.to] = d[u] + delta*e.cost - fun[e.to];
                if (!inq[e.to]) {
                    Q.push(e.to);
                    inq[e.to] = true;
                    times[e.to] += 1;
                    if (times[e.to] > n) return false;
                }
            }
        }
    }
    return true;
}

int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &fun[i]);
            G[i].clear();
        }
        for (int i = 0; i < m; i++) {
            int u, v, cost;
            scanf("%d%d%d", &u, &v, &cost);
            G[u].push_back(edge(v, cost));
        }
        int l = 0, r = 10000000;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (SPFA(1, n, mid*1.0/1000))
                r = mid - 1;
            else 
                l = mid + 1;
        }
        if (r % 10 > 4)
            r = (r/10+1) * 10;
        else 
            r = (r/10) * 10;
        printf("%.2lf\n", r*1.0/1000);
    }
    return 0;
}