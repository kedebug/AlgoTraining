#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>
#define MAXN 5005
using namespace std;

/*
题意:
    给定一个行数和列数固定的网格,再给定若干个点,这些点是使用矩形上网格线交叉点的
    坐标来唯一确定的R行C列的网格,左上角的坐标为(1,1)右下角的坐标为(R,C),问给定的
    这些点能够组成最长可能路径是多长. 路径的定义的如下的:由若干连续且间隔相等的
    点组成,方向可任意,起始点和结束点均在网格之外的任意空间.也就是只要满足网格内
    连续两点之间的间距相等就可以了. 路径上要求至少三个点,而且起点和终点一定要在
    网格的外部. 
    
解法:
    搜索+剪枝
    直接枚举按照x,y排序的序列,直接枚举2个点作为开始点,有三个的地方需要剪枝,这样
    跑起来更快速 
*/

int R, C, N;
char G[MAXN][MAXN]; // 开char能保留更多信息,比bool划算 

struct Node {
    int x, y;
}e[5005];

bool cmp(Node a, Node b) {
    if (a.x != b.x) {
        return a.x < b.x;
    } else {
        return a.y < b.y;
    }
}

bool judge(int x, int y) {
    if (x > 0 && x <= R && y > 0 && y <= C) {
        return true;    
    }
    return false;
}

int deal() {
    int ret = 2, length, cx, cy, dx, dy, px, py;
    for (int i = 1; i < N; ++i) { // N不会和任何点组成一个点对
        for (int j = i+1; j <= N; ++j) {
            length = 2, cx = e[j].x, cy = e[j].y, dx = e[j].x-e[i].x, dy = e[j].y-e[i].y;
            px = e[i].x-dx, py = e[i].y-dy; 
            if (cx+(ret-2)*dx>R) break; 
            // 假设后面每间隔都有一个点都无法达到已有的最大值,由于排序中x是绝对非递减的,所以直接break 
            if (cy+(ret-2)*dy<1 || cy+(ret-2)*dy>C) continue; 
            // 同理,只不过y的值并没有从小到大的规律 
            if (judge(px, py)) continue;
            // 如果计算出来的点在内部,这个点如果没有覆盖就不能走,如果覆盖了那么这条路径就已经寻找过 
            while (judge(cx+dx, cy+dy) && G[cx+dx][cy+dy]) {
                ++length;
                cx += dx, cy += dy;
            }
            if (!judge(cx+dx, cy+dy)) { // 落在外面
                ret = max(ret, length);
            }
        }
    }
    return ret >= 3 ? ret : 0;
}

int main() {
    while (scanf("%d %d", &R, &C) == 2) {
        memset(G, 0, sizeof (G));
        scanf("%d", &N);
        for (int i = 1; i <= N; ++i) {
            scanf("%d %d", &e[i].x, &e[i].y);
            G[e[i].x][e[i].y] = 1;
        }
        sort(e+1, e+1+N, cmp); // 按照cmp排序后,能够保证所有路径的前两个点一定能够枚举到 
        printf("%d\n", deal());
    }
    return 0;
}