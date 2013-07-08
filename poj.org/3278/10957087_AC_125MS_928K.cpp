
#include <cstdio>
#include <cstdlib>
#include <queue>

using namespace std;

const int MAXN = 100010;
int n, k;
bool vis[MAXN];
int cost[MAXN];

int bfs()
{
    queue<int> q;
    q.push(n);
    cost[n] = 0;
    vis[n] = true;

    while (!q.empty())
    {
        int p;
        p = q.front();
        q.pop();

        if (p == k)
            return cost[p];

        if (p-1 >= 0 && !vis[p-1])
        {
            cost[p-1] = cost[p] + 1;
            vis[p-1] = true;
            q.push(p-1);
        }
        if (p+1 <= 100000 && !vis[p+1])
        {
            cost[p+1] = cost[p] + 1;
            vis[p+1] = true;
            q.push(p+1);
        }
        if (p * 2 <= 100000 && !vis[p*2])
        {
            cost[p*2] = cost[p] + 1;
            vis[p*2] = true;
            q.push(p*2);
        }
    }
    return 0;
}

int main()
{
    scanf("%d %d", &n, &k);
    memset(vis, false, sizeof(vis));
    memset(cost, 0, sizeof(cost));
    printf("%d\n", bfs());
    return 0;
}