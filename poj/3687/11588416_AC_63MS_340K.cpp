
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 210;
vector<int> G[MAXN];
int arr[MAXN], indeg[MAXN];

bool judge(int u, int v) {
    for (int i = 0; i < G[u].size(); i++)
        if (G[u][i] == v) return false;
    return true;
}

int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            G[i].clear(), indeg[i] = 0;
        while (m--) {
            int u, v;
            scanf("%d%d", &v, &u);
            if (judge(u, v)) {
                G[u].push_back(v);
                indeg[v] += 1;
            }
        }
        int w;
        for (w = n; w >= 1; w--) {
            int i;
            for (i = n; i >= 1; i--)
                if (!indeg[i]) break;
            if (i == 0) break;
            
            arr[i] = w;
            indeg[i] = -1;

            for (int j = 0; j < G[i].size(); j++) {
                int v = G[i][j];
                if (indeg[v] > 0) 
                    indeg[v] -= 1;
            }   
        }
        if (w != 0) 
            printf("-1\n");
        else {
            for (int i = 1; i <= n; i++)
                printf("%d ", arr[i]);
            printf("\n");
        }
    }
    return 0;
}