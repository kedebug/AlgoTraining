#include <cstdio>
#include <cstring>
#include <iostream>
#define maxn 1007
#define inf 99999999
using namespace std;
int dis[maxn],map[maxn][maxn],maxd[maxn][maxn];
int pre[maxn],stack[maxn];
bool vt[maxn];
int n,m,ans;
void init()
{
    int i,j;
    for (i = 0; i < maxn; ++i)
    {
        for (j = 0; j < maxn; ++j)
        {
            if (i == j) map[i][j] = 0;
            else map[i][j] = inf;
            maxd[i][j] = -1;
        }
    }
}
void prim()
{
    int i,j,Min,k;
    int top = 0; ans = 0;
    for (i = 1; i <= n; ++i)
    {
        pre[i] = 1;//存放i的父节点
        dis[i] = map[1][i];
        vt[i] = false;
    }
    vt[1] = true;
    stack[top++] = 1;//存放已经加入最小生成树节点
   for (k = 1; k < n; ++k)
   {
       j = 1; Min = inf;
       for (i = 2; i <= n; ++i)
       {
           if (!vt[i] && dis[i] < Min)
           {
               j = i; Min = dis[i];
           }
       }
       vt[j] = true; ans += Min;
       //关键是这里运用DP求任意两点的最大边权
       for (i = 0; i < top; ++i)
       maxd[j][stack[i]] = maxd[stack[i]][j] = max(Min,maxd[stack[i]][pre[j]]);
       stack[top++] = j;
       for (i = 2; i <= n; ++i)
       {
           if (!vt[i] && dis[i] > map[i][j] && map[i][j] != inf)
           {
               dis[i] = map[i][j];
               pre[i] = j;//记录父节点
           }
       }
   }

}
int main()
{
    int i,j,t;
    int x,y,z;
    scanf("%d",&t);
    while (t--)
    {
        init();
        scanf("%d%d",&n,&m);
        for (i = 0; i < m; ++i)
        {
            scanf("%d%d%d",&x,&y,&z);
            map[x][y] = map[y][x] = z;
        }
        prim();
        int ct = inf;
        //循环加外边计算差值
        for (i = 1; i <= n; ++i)
        {
            for (j = 1; j <= n; ++j)
            {
                if (i != j && pre[j] != i && j != pre[i] && map[i][j] != inf)
                {
                    //printf(">>>%d %d\n",map[i][j],maxd[i][j]);
                    ct = min(map[i][j] - maxd[i][j],ct);
                }
            }
        }
        if (ct == 0) printf("Not Unique!\n");
        else         printf("%d\n",ans);
    }
}