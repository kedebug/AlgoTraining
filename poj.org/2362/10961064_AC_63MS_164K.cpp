
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAXN = 25;
bool vis[MAXN];
int stick[MAXN];

int n, edge;

bool dfs(int s, int c, int len)
{
    if (c == 3 && len == edge)
        return true;

    if (len == edge)
        ++c, len = 0, s = 0;

    int i;
    for (i = s; i < n; ++i)
    {
        if (!vis[i])
        {
            vis[i] = true;
            if (len + stick[i] <= edge && dfs(i + 1, c, len + stick[i]))
                return true;
            vis[i] = false;
            if (len == 0)
                return false;
        }
    }
    return false;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int i;
        int sum = 0;

        scanf("%d", &n);
        memset(stick, 0, sizeof(stick));
        memset(vis, false, sizeof(vis));
        for (i = 0; i < n; ++i)
        {
            scanf("%d", &stick[i]);
            sum += stick[i];
        }

        edge = sum / 4;
        if (sum % 4 == 0 && dfs(0, 0, 0))
            printf("yes\n");
        else 
            printf("no\n");
    }
    return 0;
}