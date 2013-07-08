
// http://blog.sina.com.cn/s/blog_81f8b0e20100x4sn.html

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 301;
bool vis[MAXN][MAXN];
int dir[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                 {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

typedef struct _Point {
    int x, y;
    int step;
} point;

point startp, endp;

bool judge(int x, int y, int n)
{
    if (0 <= x && x < n && 0 <= y && y < n)
        return true;
    return false;
}

void bfs(int n)
{
    memset(vis, false, sizeof(vis));
    vis[startp.x][startp.y] = true;
    startp.step = 0;
    endp.step = MAXN * MAXN;

    queue<point> q;
    point s, e;
    q.push(startp);

    while (!q.empty())
    {
        s = q.front();
        q.pop();
        for (int i = 0; i < 8; ++i)
        {
            e.x = s.x + dir[i][0];
            e.y = s.y + dir[i][1];
            e.step = s.step + 1;
            if (judge(e.x, e.y, n) && !vis[e.x][e.y])
            {
                vis[e.x][e.y] = true;
                q.push(e);
                if (e.x == endp.x && e.y == endp.y)
                    if (e.step < endp.step)
                        endp.step = e.step;
            }
        }
    }
}

int main()
{
    int n, l;
    scanf("%d", &n);

    while (n--)
    {
        scanf("%d", &l);

        int sx, sy, ex, ey;
        scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
        startp.x = sx, startp.y = sy;
        endp.x = ex, endp.y = ey;
        if (sx == ex && sy == ey)
            printf("0\n");
        else
        {
            bfs(l);
            printf("%d\n", endp.step);
        }
    }
    return 0;
}