#include <iostream>
#include <cmath>
using namespace std;
#define INF 1000000
int mins[21], minv[21];
#define min(a, b) ((a) < (b) ? (a) : (b))
int n, m, best;
void init()
{
    int i;
    for(i = 1; i < 21; i++)
    {							//注意此题所有半径和高度都是正整数，所以可得下面的式子
        mins[i] = mins[i - 1] + 2 * i * i;		//mins表示从最上面一层到 i 层的最小表面积(这里仅仅算了侧面)
        minv[i] = minv[i - 1] + i * i * i;		//minv表示从最上面一层到 i 层的最小体积
    }
}
//dfs从m层开始向上搜索，一直搜索到0层结束
//deep表示该层层数，sums表示在deep + 1 -> m得到的表面积， sumv表示deep + 1 -> m得到的体积，r表示deep + 1的半径，h表示deep + 1的高度
void dfs(int deep, int sums, int sumv, int r, int h)		
{
    if(deep == 0)
    {
        if(sumv == n && sums < best)
            best = sums;
        return ;
    }
    //这里用到的三个剪枝
    //sums + mins[deep]> best 表示以前的到的deep + 1层到 m 层的表面积加上从顶层到deep层的最小表面积如果都大于了已经得到的best,那么1到deep层是无论半径和高度取何值都是无效的
    //sumv + minv[deep] > n同理
    // 2 * (n - sumv) / r + sums >= best 这是该题的精髓，如果没有的话会造成超时，是为了把sumv和sums联系起来，原因如下:
    // 假设能够得到best时(为什么这样假设呢，因为如果得不到的话那么就已经被第一个剪枝滤去了,所以在第三个剪枝验证时表示已经通过了第一个剪枝的要求)，
    // n - sumv = h[1] * r[1] * r[1] + ... + h[deep] * r[deep] * r[deep] < h[1] * r[1] * r + ... + h[deep] * r[deep] * r （因为r是deep + 1层的半径）
    //其中h[1]...h[deep]表示在函数的形参情况下，1到deep层应该取得h值，r[1]同理
    // 两边同时处以r 再乘以2得 2 * (n - sumv) / r < 2 * (h[1] * r[1] + ... + h[deep] * r[deep]) 
    // 2 * (n - sumv) / r < best - sums
    // 2 * (n - sumv) / r + sums < best 成立 ，则可得剪枝条件
    if(sums + mins[deep] > best || sumv + minv[deep] > n || (2 * (n - sumv) / r + sums >= best))		
        return;
    int i, j,  maxh;
    for(i = r - 1; i >= deep; i--)
    {
        if(deep == m)
            sums = i * i;
        maxh = min(n - sumv - minv[deep - 1] / i * i, h - 1);
        for(j = maxh; j >= deep; j--)
            dfs(deep - 1, sums + 2 * i * j, sumv + j * i * i, i, j);
    }
}
int main()
{
    best = INF;   //将best置成一个很大的值
    cin >> n >> m;
    dfs(m, 0, 0, sqrt((double)n) + 1, n + 1);  //初始条件m层上一层的半径为sqrt(n) + 1是在h等于1时得到的上限，高度h表示半径为1时得到的上限
    if(best == INF)
        cout << 0 << endl;
    else
        cout << best << endl;
    return 0;
}