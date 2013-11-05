
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 1 << 16;
int vis[MAXN], src;
int dir[5][2] = { 0,0,0,1,1,0,0,-1,-1,0 };
int bit[17];

int bfs()
{
    if (src == 0 || src == MAXN-1)
        return 0;
    queue<int> q;
    q.push(src);
    vis[src] = 1;

    int i, j, k;
    int p, pt;
    while (!q.empty())
    {
        p = q.front();
        q.pop();
        for (i = 0; i < 4; ++i)
        {
            for (j = 0; j < 4; ++j)
            {
                int x, y;
                pt = p;
                for (k = 0; k < 5; ++k)
                {
                    x = i + dir[k][0];
                    y = j + dir[k][1];
                    if (0 <= x && x < 4 && 0 <= y && y < 4)
                        pt ^= bit[x*4+y];
                }
                if (pt == 0 || pt == MAXN-1)
                    return vis[p];
                if (vis[pt] == 0)
                {
                    vis[pt] = vis[p] + 1;
                    q.push(pt);
                }
            }
        }
    }
    return -1;
}

int main()
{
    char mat[5][5];
    int i, j;

    for (i = 0; i < 17; ++i)
        bit[i] = 1 << i;

    src = 0;

    for (i = 0; i < 4; ++i)
    {
        scanf("%s", mat[i]);
        for (j = 0; j < 4; ++j)
            if (mat[i][j] == 'b')
                src |= bit[i*4+j];
    }
    int res = bfs();
    printf(res == -1 ? "Impossible\n":"%d\n", res);
    return 0;
}
