
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int MAXN = 110;
vector<int> G[MAXN];stack<int> S;
int dfn[MAXN], low[MAXN], sccno[MAXN], tclock, sccnum;
int indeg[MAXN], outdeg[MAXN];

void tarjan(int u) {
	dfn[u] = low[u] = ++tclock;
	S.push(u);

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (!sccno[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}

	if (dfn[u] == low[u]) {
		sccnum += 1;
		int v = -1;
		while (u != v) {
			v = S.top();
			S.pop();
			sccno[v] = sccnum;
		}
	}
}

void findscc(int n) {
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(sccno, 0, sizeof(sccno));
	tclock = sccnum = 0;
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) tarjan(i);
}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		G[i].clear();
		int v;
		while (scanf("%d", &v) && v)
			G[i].push_back(v);
	}
	findscc(n);
	memset(indeg, 0, sizeof(indeg));
	memset(outdeg, 0, sizeof(outdeg));
	for (int u = 1; u <= n; u++) {
		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i];
			if (sccno[u] != sccno[v]) {
				indeg[sccno[v]] += 1;
				outdeg[sccno[u]] += 1;
			}
		}
	}
	int ans1 = 0, ans2 = 0;
	for (int i = 1; i <= sccnum; i++) {
		if (!indeg[i]) ans1 += 1;
		if (!outdeg[i]) ans2 += 1;
	}
	if (sccnum == 1)
		printf("1\n0\n");
	else
		printf("%d\n%d\n", ans1, max(ans1, ans2));

	return 0;
}