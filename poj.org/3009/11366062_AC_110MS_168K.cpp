#include <stdio.h>
#define MIN(x, y) (x)<(y)?(x):(y)
#define MAXN 25
#define INF 15
int w, h, result, map[MAXN][MAXN];
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, -1, 0, 1};
bool in(int tx, int ty)
{
    return tx >= 1 && tx <= w && ty >= 1 && ty <= h;
}
void dfs(int x, int y, int step)
{
    bool out;
    int i, tx, ty;
    if (step > 10) // 终止条件
        return;
    for (i = 0; i < 4; ++i)
    {
        if (map[x+dx[i]][y+dy[i]] == 1) // 与石头相邻
            continue;
        out = false;
        tx = x;
        ty = y;
        while (1) // 沿一方向滑行
        {
            tx += dx[i];
            ty += dy[i];
            if (!in(tx, ty)) // 一定要先判定出界情况! 这里WA了一次
            {
                out = true;
                break;
            }
            else if (map[tx][ty] == 3) // 到达终点
            {
                result = MIN(result, step);
                return;
            }
            else if (map[tx][ty] == 1) // 打到石块
                break;
        }
        if (out) // 出界则剪枝
            continue;
        map[tx][ty] = 0; // 破坏石头
        dfs(tx-dx[i], ty-dy[i], step+1);
        map[tx][ty] = 1;
    }
}
int main()
{
    int i, j, s_x, s_y;
    while (scanf("%d%d", &w, &h), w && h)
    {
        for (i = 1; i <= h; ++i)
            for (j = 1; j <= w; ++j)
            {
                scanf("%d", &map[j][i]);
                if (map[j][i] == 2)
                {
                    s_x = j;
                    s_y = i;
                    map[j][i] = 0; // 找到起点后清空该位置
                }
            }
        result = INF;
        dfs(s_x, s_y, 1);
        if (result == INF)
            printf("-1\n");
        else
            printf("%d\n", result);
    }
    return 0;
}