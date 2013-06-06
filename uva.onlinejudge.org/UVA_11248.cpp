//
//#include <cstdio>
//#include <cstring>
//#include <vector>
//#include <queue>
//#include <algorithm>
//using namespace std;
//
//const int MAXN = 110;
//const int INFS = 0x3FFFFFFF;
//
//struct edge {
//    int from, to, cap, flow;
//    edge(int _from, int _to, int _cap, int _flow) 
//        : from(_from), to(_to), cap(_cap), flow(_flow) {}
//    bool operator < (const edge& rhs) const {
//        if (from == rhs.from) return to < rhs.to;
//        return from < rhs.from;
//    }
//};
//
//class ISAP {
//public:
//    void clearall(int n) {
//        this->n = n;
//        for (int i = 0; i < n; i++)
//            G[i].clear();
//        edges.clear();
//    }
//    bool bfs() {
//        queue<int> Q;
//        d[t] = 0;
//        memset(vis, false, sizeof(vis));
//        vis[t] = true;
//        Q.push(t);
//        while (!Q.empty()) {
//            int x = Q.front(); Q.pop();
//            for (int i = 0; i < G[x].size(); i++) {
//                edge& e = edges[G[x][i]^1];
//                if (!vis[e.from] && e.cap > e.flow) {
//                    vis[e.from] = true;
//                    d[e.from] = d[x] + 1;
//                    Q.push(e.from);
//                }
//            }
//        }
//        return vis[s];
//    }
//
//    void addedge(int u, int v, int cap) {
//        edges.push_back(edge(u, v, cap, 0));
//        edges.push_back(edge(v, u, 0, 0));
//        G[u].push_back(edges.size() - 2);
//        G[v].push_back(edges.size() - 1);
//    }
//    int augment() {
//        int x = t, a = INFS;
//        while (x != s) {
//            edge& e = edges[p[x]];
//            a = min(a, e.cap - e.flow);
//            x = e.from;
//        }
//        x = t;
//        while (x != s) {
//            edges[p[x]].flow += a;
//            edges[p[x]^1].flow -= a;
//            x = edges[p[x]].from;
//        }
//        return a;
//    }
//    int maxflow(int s, int t, int need) {
//        this->s = s, this->t = t;
//        bfs();
//        memset(gap, 0, sizeof(gap));
//        for (int i = 0; i < n; i++) 
//            cur[i] = 0, gap[d[i]] += 1;
//
//        int x = s, flow = 0;
//        while (d[s] < n) {
//            if (x == t) {
//                flow += augment();
//                if (flow >= need) return flow;
//                x = s;
//            }
//            bool flag = false;
//            for (int i = cur[x]; i < G[x].size(); i++) {
//                edge& e = edges[G[x][i]];
//                if (e.cap > e.flow && d[x] == d[e.to] + 1) {
//                    flag = true;
//                    cur[x] = i;
//                    p[e.to] = G[x][i];
//                    x = e.to;
//                    break;
//                }
//            }
//            if (!flag) {
//                int m = n - 1;
//                for (int i = 0; i < G[x].size(); i++) {
//                    edge& e = edges[G[x][i]];
//                    if (e.cap > e.flow)
//                        m = min(m, d[e.to]);
//                }
//                if (--gap[d[x]] == 0) break;
//                gap[d[x] = m+1] += 1;
//                cur[x] = 0;
//                if (x != s) x = edges[p[x]].from;
//            }
//        }
//        return flow;
//    }
//    void mincut(vector<int>& cut) {
//        bfs();
//        for (int i = 0; i < edges.size(); i++) {
//            edge& e = edges[i];
//            if (!vis[e.from] && vis[e.to] && e.cap > 0)
//                cut.push_back(i);
//        }
//    }
//    void reduce() {
//        for (int i = 0; i < edges.size(); i++)
//            edges[i].cap -= edges[i].flow;
//    }
//    void clearflow() {
//        for (int i = 0; i < edges.size(); i++)
//            edges[i].flow = 0;
//    }
//public:
//    int n, s, t;
//    vector<edge> edges;
//    vector<int> G[MAXN];
//    int p[MAXN], d[MAXN], cur[MAXN], gap[MAXN];
//    bool vis[MAXN];
//};
//
//ISAP sap;
//
//int main() {
//    int n, e, c, cases = 0;
//    while (scanf("%d%d%d", &n, &e, &c) && n) {
//        sap.clearall(n);
//        while (e--) {
//            int u, v, fp;
//            scanf("%d%d%d", &u, &v, &fp);
//            sap.addedge(u - 1, v - 1, fp);
//        }
//        int flow = sap.maxflow(0, n - 1, INFS);
//        printf("Case %d: ", ++cases);
//        if (flow >= c) {
//            printf("possible\n");
//        } else {
//            vector<int> cut;
//            vector<edge> ans;
//            sap.mincut(cut);
//            sap.reduce();
//            for (int i = 0; i < cut.size(); i++) {
//                edge& e = sap.edges[cut[i]];
//                sap.clearflow();
//                e.cap = c;
//                if (flow + sap.maxflow(0, n - 1, c - flow) >= c)
//                    ans.push_back(e);
//                e.cap = 0;
//            }
//            if(ans.empty()) 
//                printf("not possible\n");
//            else {
//                sort(ans.begin(), ans.end());
//                printf("possible option:(%d,%d)", ans[0].from + 1, ans[0].to + 1);
//                for(int i = 1; i < ans.size(); i++)
//                    printf(",(%d,%d)", ans[i].from + 1, ans[i].to + 1);
//                printf("\n");
//            }
//        }
//    }
//    return 0;
//}