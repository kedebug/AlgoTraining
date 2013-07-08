/*
ID: sdj22251
PROG: inflate
LANG: C++
*/
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#define MAXN 105
#define INF 1000000000
using namespace std;
struct wwj
{
    int pos;
    char x[12];
}tmp;
int top, found, st[400000], mi;
int d[] = {-1, -3, 1, 3};
char as[] = "lurd";
bool move[][4] = {{0,0,1,1}, {1,0,1,1}, {1,0,0,1}, {0,1,1,1}, {1,1,1,1}, {1,1,0,1}, {0,1,1,0}, {1,1,1,0}, {1,1,0,0}};
int h(wwj &t)
{
    int sum = 0;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            int k = i * 3 + j;
            if(t.x[k] == 'x') continue;
            sum += abs(i - (t.x[k] - '1') / 3) + abs(j - (t.x[k] - '1') % 3);
        }
    return sum;
}
void output()
{
    for(int i = 1;i <= top; i++) printf("%c", as[st[i]]);
    printf("\n");
}
void dfs(int p, int dp, int maxdp)
{
    int f = h(tmp);
    int i, t;
    if(mi > f) mi = f;
    if(f + dp > maxdp || found) return;
    if(f == 0)
    {
        output();
        found = 1;
        return;
    }
    for(i = 0;i < 4; i++)
    {
        if(move[p][i] == 0) continue;
        t = d[i] + p;
        if(top > 0 && d[st[top]] + d[i] == 0) continue;  //一个重要的剪枝，如果之前的一步和现在的一步是相反的，无疑是做了无用功，不必搜索。
        swap(tmp.x[t], tmp.x[p]);
        st[++top] = i;
        dfs(t, dp + 1, maxdp);
        top--;
        swap(tmp.x[t], tmp.x[p]);
    }
}
void IDA()
{
    int maxdp = h(tmp);//初始为初状态的h值
    found = 0;
    while(found == 0)
    {
        mi = 0x7fffffff; //mi表示在当前的h值限制下所能搜到的最优位置，即h值最小的位置
        top = 0;
        dfs(tmp.pos, 0, maxdp);
        maxdp += mi; //如果不能搜到就将mi加上去
    }
}
int main()
{
    for(int i = 0; i < 9; i++)
    {
        scanf("%s", &tmp.x[i]);
        if(tmp.x[i] == 'x') tmp.pos = i;
    }
    IDA();
    return 0;
}
