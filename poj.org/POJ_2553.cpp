//
//#include <iostream>
//#include <vector>
//#include <stack>
//#include <algorithm>
//using namespace std;
//
//const int MAXN = 5010;
//vector<int> G[MAXN];
//stack<int> S;
//int dfn[MAXN], low[MAXN], sccno[MAXN], sccnum, tclock;
//int indeg[MAXN], outdeg[MAXN];
//
//void tarjan(int u) {
//    dfn[u] = low[u] = ++tclock;
//    S.push(u);
//
//    for (int i = 0; i < G[u].size(); i++) {
//        int v = G[u][i];
//        if (!dfn[v]) {
//            tarjan(v);
//            low[u] = min(low[u], low[v]);
//        } else if (!sccno[v]) {
//            low[u] = min(low[u], dfn[v]);
//        }
//    }
//
//    if (dfn[u] == low[u]) {
//        sccnum += 1;
//        int v = -1;
//        while (v != u) {
//            v = S.top();
//            S.pop();
//            sccno[v] = sccnum;
//        }
//    }
//}
//
//void findscc(int n) {
//    for (int i = 0; i <= n; i++)
//        dfn[i] = low[i] = sccno[i] = 0;
//    sccnum = tclock = 0;
//    for (int i = 1; i <= n; i++)
//        if (!dfn[i]) tarjan(i);
//}
//
//int main() {
//    int n, e;
//    while (scanf("%d", &n) && n) {
//        scanf("%d", &e);
//        for (int i = 1; i <= n; i++)
//            G[i].clear();
//        for (int i = 0; i < e; i++) {
//            int u, v;
//            scanf("%d%d", &u, &v);
//            G[u].push_back(v);
//        }
//        findscc(n);
//        for (int i = 1; i <= n; i++)
//            indeg[i] = outdeg[i] = 0;
//        for (int u = 1; u <= n; u++) {
//            for (int i = 0; i < G[u].size(); i++) {
//                int v = G[u][i];
//                if (sccno[u] != sccno[v]) {
//                    indeg[sccno[v]] += 1;
//                    outdeg[sccno[u]] += 1;
//                }
//            }
//        }
//        for (int i = 1; i <= n; i++) {
//            if (!outdeg[sccno[i]]) 
//                printf("%d ", i);
//        }
//        printf("\n");
//    }
//    return 0;
//}