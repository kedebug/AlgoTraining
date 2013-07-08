
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

#define max(a, b)  ((a) > (b) ? (a) : (b))
const int MAXN = 20010;
vector<int> map[MAXN];
int f[MAXN], balance[MAXN];
int n;

void build_tree(int u)
{
    int i, v;
    for (i = 0; i < map[u].size(); ++i)
    {
        v = map[u][i];
        if (f[u] == v)
            continue;
        f[v] = u;
        build_tree(v);
    }
}

int dfs(int u)
{
    int tmax = 0, sum = 0;
    for (int i = 0; i < map[u].size(); ++i)
    {
        int v = map[u][i];
        if (f[u] == v)
            continue;
        int child = dfs(v);
        sum += child;
        tmax = max(child, tmax);
    }
    balance[u] = max(tmax, n - sum - 1);
    return sum + 1;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int i, j;
        int a, b;

        scanf("%d", &n);
        for (i = 1; i <= n; ++i)
            map[i].clear(), f[i] = -1;

        for (i = 1; i < n; ++i)
        {
            scanf("%d %d", &a, &b);
            map[a].push_back(b);
            map[b].push_back(a);
        }
       
        build_tree(1);  //  1 is regarded as the root of the tree
        dfs(1);
        int num, ans;
        ans = MAXN;
        for (i = 1; i <= n; ++i)
            if (ans > balance[i])
                ans = balance[i], num = i;
        printf("%d %d\n", num, ans);
    }
    return 0;
}