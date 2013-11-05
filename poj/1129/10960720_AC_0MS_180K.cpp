
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 32;
bool map[MAXN][MAXN];
bool vis[MAXN];

int n;

void dfs(int m)
{
    vector<int> q;
    int i, j;

    q.clear();
    q.push_back(m);

    for (i = 1; i <= n; ++i)
    {
        if (!vis[i] && !map[m][i])
        {
            bool flag = true;
            for (j = 0; j < q.size(); ++j)
                if (map[i][q[j]])
                {
                    flag = false;
                    break;
                }
            if (flag)
            {
                q.push_back(i);
                vis[i] = true;
            }
        }
    }
}

int main()
{
    while (scanf("%d", &n) && n)
    {
        int i, j;
        char s[MAXN];

        memset(map, false, sizeof(map));
        memset(vis, false, sizeof(vis));

        for (i = 1; i <= n; ++i)
        {
            scanf("%s", s);
            for (j = 2; s[j] != '\0'; ++j)
                map[i][s[j]-'A'+1] = true;
        }
        int ans = 0;
        for (i = 1; i <= n; ++i)
        {
            if (!vis[i])
            {
                vis[i] = true;
                dfs(i);
                ++ans;
            }
        }
        if (ans == 1)
            printf("%d channel needed.\n", ans);
        else
            printf("%d channels needed.\n", ans);
    }
    return 0;
}