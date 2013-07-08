
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 110;
const int INFS = 0x3FFFFFFF;

struct edge {
    int u, v, w;
    edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
    bool operator < (const edge& o) { return w < o.w; }
};

vector<edge> edges;
int f[MAXN];

int find(int x) {
    int r = x;
    while (r != f[r])
        r = f[r];

    while (x != r) {
        int t = f[x];
        f[x] = r, x = t;
    }
    return r;
}

void merge(int a, int b) { f[a] = b; }

int kruskal(int n) {
    int ans = INFS;

    for (int i = 0; i < edges.size(); i++) {
        if (i + n - 1 > edges.size())
            break;

        for (int k = 1; k <= n; k++) 
            f[k] = k;
        int cflag = 0;
        for (int j = i; j < edges.size(); j++) {
            int ru = find(edges[j].u);
            int rv = find(edges[j].v);
            if (ru == rv) continue;
            merge(ru, rv);
            cflag += 1;
            if (cflag == n - 1) {
                ans = min(ans, edges[j].w - edges[i].w);
                break;
            }
        }
    }
    return ans == INFS ? -1 : ans;
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) && (n || m)) {
        edges.clear();
        for (int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            edges.push_back(edge(a, b, c));
        }
        sort(edges.begin(), edges.end());
        printf("%d\n", kruskal(n));
    }
    return 0;
}