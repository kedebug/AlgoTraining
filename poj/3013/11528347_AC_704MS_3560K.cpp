
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 50010;
const __int64 INFS = 0x3FFFFFFF7FFFFFFF;

struct edge {
    int v;
    __int64 cost;
    edge* next;
} *V[MAXN], ES[MAXN*2];

int EC;
__int64 d[MAXN], weight[MAXN];
bool inq[MAXN];

void addedge(int u, int v, int cost) {
    ES[++EC].next = V[u]; 
    V[u] = ES + EC;
    V[u]->v = v, V[u]->cost = cost;
}

void SPFA(int s, int n) {
    for (int i = 1; i <= n; i++)
        d[i] = INFS, inq[i] = false;
    queue<int> Q;
    Q.push(s);
    d[s] = 0, inq[s] = true;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        inq[u] = false;
        for (edge* e = V[u]; e; e = e->next) {
            if (d[e->v] > d[u] + e->cost) {
                d[e->v] = d[u] + e->cost;
                if (!inq[e->v]) { 
                    inq[e->v] = true; Q.push(e->v); 
                }
            }
        }
    }
}

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        int n, e;
        scanf("%d%d", &n, &e);
        for (int i = 1; i <= n; i++) {
            scanf("%I64d", &weight[i]);
            V[i] = 0;
        }
        EC = 0;
        for (int i = 0; i < e; i++) {
            int u, v;
            __int64 cost;
            scanf("%d%d%I64d", &u, &v, &cost);
            addedge(u, v, cost);
            addedge(v, u, cost);
        }
        SPFA(1, n);
        __int64 ans = 0;
        bool flag = false;
        for (int i = 1; i <= n; i++) {
            ans += weight[i] * d[i];
            if (d[i] == INFS) {
                flag = true; break;
            }
        }
        if (flag) 
            printf("No Answer\n");
        else 
            printf("%I64d\n", ans);
    }
    return 0;
}