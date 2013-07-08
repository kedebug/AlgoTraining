
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 1010;
const int MAXM = 100010;
const int INFS = 0x3f3f3f3f;

struct ST {
    int v, cost, f;
    ST() {}
    ST(int _v, int _cost, int _f) : v(_v), cost(_cost), f(_f) {}
    bool operator < (const ST& other) const { return f > other.f; }
};

struct edge {
    int v, cost;
    edge *next;
} *V[MAXN], ES[MAXM], *V2[MAXN], ES2[MAXM];

int EC, EC2, dis[MAXN], N, M, S, T, K;

void addedge(int u, int v, int cost) {
    ES[++EC].next = V[u]; 
    V[u] = ES + EC;
    V[u]->v = v, V[u]->cost = cost;
}

vector<ST> P[MAXN];
vector<ST> G[MAXN];

void addedge2(int u, int v, int cost) {
    ES2[++EC2].next = V[u]; 
    V2[u] = ES2 + EC2;
    V2[u]->v = v, V2[u]->cost = cost;
}

//void spfa(int s) {
//    bool vis[MAXN];
//    for (int i = 1; i <= N; i++) 
//        dis[i] = INFS, vis[i] = false;
//    dis[s] = 0;
//
//    //priority_queue<ST> Q;
//    //Q.push(ST(s, 0, 0));
//
//    //while (!Q.empty()) {
//    //    ST u = Q.top();
//    //    Q.pop();
//
//    //    if (vis[u.v]) 
//    //        continue;
//    //    vis[u.v] = true;
//
//    //    for (edge* e = V2[u.v]; e; e = e->next) {
//    //        if (!vis[e->v] && dis[e->v] > dis[u.v] + e->cost) {
//    //            dis[e->v] = dis[u.v] + e->cost;
//    //            Q.push(ST(e->v, dis[e->v], dis[e->v]));
//    //        }
//    //    }
//    //}
//    queue<ST> Q;
//    ST x;
//    x.v = s, x.cost = 0, x.f = 0;
//    Q.push(x);
//    vis[s] = true;
//
//    while (!Q.empty()) {
//        ST u = Q.front();
//        Q.pop();
//
//        vis[u.v] = false;
//        for (edge* e = V2[u.v]; e; e = e->next) {
//            if (dis[e->v] > dis[u.v] + e->cost) {
//                dis[e->v] = dis[u.v] + e->cost;
//                if (!vis[e->v]) {
//                    vis[e->v] = true;
//                    x.v = e->v, x.cost = 0, x.f = 0;
//                    Q.push(x);
//                }
//            }
//        }
//    }
//}

void spfa(int src)
{
    queue<int> q;
    bool inq[MAXN] = {0};
    for(int i = 1; i <= N; i++) dis[i] = (i == src)?0:INFS;
    q.push(src);
    while(!q.empty())
    {
        int x = q.front(); q.pop();
        inq[x] = 0;
        for(int i = 0; i < G[x].size(); i++)
        {
            int v = G[x][i].v, w = G[x][i].cost;
            if(dis[v] > dis[x] + w)
            {
                dis[v] = dis[x] + w;
                if(!inq[v])
                {
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}

int bfs(int src, int dst) {
    if (dis[src] == INFS)
        return -1;

    int count[MAXN];
    memset(count, 0, sizeof(count));
    priority_queue<ST> Q;
    ST x;
    x.v = src, x.cost = 0, x.f = dis[src];
    Q.push(x);

    while (!Q.empty()) {
        ST u = Q.top();
        Q.pop();

        count[u.v] += 1;
        if (count[dst] == K)
            return u.cost;

        for (int i = 0; i < P[u.v].size(); i++) {
            x.v = P[u.v][i].v, x.cost = u.cost + P[u.v][i].cost, x.f = x.cost + dis[x.v];
            Q.push(x);
        }
    }
    return -1;
}

int main() {
    while (scanf("%d%d", &N, &M) != EOF) {
        EC = EC2 = 0;
        memset(V, 0, sizeof(V));
        memset(V2, 0, sizeof(V2));
        for (int i = 0; i < M; i++) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            P[u].push_back(ST(v, c, 0));
            G[v].push_back(ST(u, c, 0));
        }
        scanf("%d%d%d", &S, &T, &K);
        if (S == T) K += 1;
        spfa(T);
        printf("%d\n", bfs(S, T));
    }
    return 0;
}