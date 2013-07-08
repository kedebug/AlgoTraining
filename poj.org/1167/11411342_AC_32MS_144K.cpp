#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 60;
const int M = 1000;

struct node
{
    int start, interval, times;
}path[M];

int n, ans, tot, ct[N];

int cmp(const void *a, const void *b)
{
    node *aa, *bb;
    aa = (node *)a;
    bb = (node *)b;
    return bb->times - aa->times;
}

bool check(int s, int t)
{
    int i;
    for(i = s; i < N; i += t)
        if(!ct[i])
            return false;
    return true;
}

void dfs(int index, int sum)
{
    int i, j, tmp, k;
    if(n == 0)
    {
        if(sum < ans)  ans = sum;
        return;
    }
    for(i = index; i<tot && path[i].times>n; i++);
    for(k = i; k < tot; k++)
    {
        if(sum+n/path[k].times >= ans)  return;
        if(check(path[k].start, path[k].interval))
        {
            tmp = path[k].interval;
            for(j = path[k].start; j < N; j += tmp)
            {
                ct[j]--;
                n--;
            }
            dfs(k, sum+1);
            for(j = path[k].start; j < N; j += tmp)
            {
                ct[j]++;
                n++;
            }
        }
    }
}

int main()
{
    int i, x, j;
    scanf("%d", &n);
    memset(ct, 0, sizeof(ct));
    for(i = 0; i < n; i++)
    {
        scanf("%d", &x);
        ct[x]++;
    }
    tot = 0;
    for(i = 0; i <= 29; i++)
    {
        if(!ct[i])  continue;
        for(j = i+1; j <= 59-i; j++)
            if(check(i, j))
            {
                path[tot].start = i;
                path[tot].interval = j;
                path[tot].times = 1 + (59-i)/j;
                tot++;
            }
    }
    qsort(path, tot, sizeof(path[0]), cmp);
    ans = 17;
    dfs(0, 0);
    printf("%d\n", ans);
    return 0;
}