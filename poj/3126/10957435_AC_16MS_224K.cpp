
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <queue>

using namespace std;

const int MAXN = 10010;
bool isprime[MAXN];
bool vis[MAXN];
int cost[MAXN];
int s, e;

void init_prime()
{
    memset(isprime, false, sizeof(isprime));
    isprime[2] = isprime[3] = isprime[5] = isprime[7] = true;

    int i, j;
    bool flag;
    for (i = 7; i < MAXN; ++i)
    {
        flag = true;
        for (j = 2; j <= sqrt((double)i); ++j)
            if (i % j == 0)
            {
                flag = false;
                break;
            }
        if (flag)
            isprime[i] = true;
    }
}

int bfs()
{
    queue<int> q;
    q.push(s);
    vis[s] = true;

    while (!q.empty())
    {
        int p;
        p = q.front();
        q.pop();

        if (p == e)
            return cost[p];
        int a, b, c, d;
        a = p / 1000;
        b = p % 1000; c = b % 100; d = c % 10;
        b = b / 100; c = c / 10; 

        int i;
        int num;
        for (i = 1; i <= 9; ++i)
        {
            num = i * 1000 + p % 1000;
            if (!vis[num] && isprime[num])
            {
                vis[num] = true;
                q.push(num);
                cost[num] = cost[p] + 1;
            }
        }
        for (i = 0; i <= 9; ++i)
        {
            num = a * 1000 + i * 100 + p % 100;
            if (!vis[num] && isprime[num])
            {
                vis[num] = true;
                q.push(num);
                cost[num] = cost[p] + 1;
            }
        }
        for (i = 0; i <= 9; ++i)
        {
            num = a * 1000 + b * 100 + i * 10 + p % 10;
            if (!vis[num] && isprime[num])
            {
                vis[num] = true;
                q.push(num);
                cost[num] = cost[p] + 1;
            }
        }
        for (i = 1; i <= 9; ++i)
        {
            num = a * 1000 + b * 100 + c * 10 + i;
            if (!vis[num] && isprime[num])
            {
                vis[num] = true;
                q.push(num);
                cost[num] = cost[p] + 1;
            }
        }
    }
    return -1;
}

int main()
{
    init_prime();
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &s, &e);
        memset(vis, false, sizeof(vis));
        memset(cost, 0, sizeof(cost));
        printf("%d\n", bfs());
    }
    return 0;
}