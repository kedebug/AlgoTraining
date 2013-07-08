
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAXN = 200010;
// c[i]树形数组，生成c[i]的数组s[i]表示，大小为i的的集合的个数
// f[i]节点i的父亲节点
// a[i]以节点i为根节点的集合元素个数，初始化为1
int c[MAXN], f[MAXN], a[MAXN];  
int n, m;

int find_set(int x)
{
    int r = x;
    while (r != f[r])
        r = f[r];
    int p = x;
    while (p != r)
    {
        p = f[p];
        f[p] = r;
    }
    return r;
}

inline int low_bit(int x)
{
    return x & (-x);
}

void add(int p, int d)
{
    for (int i = p; i <= n; i += low_bit(i))
        c[i] += d;
}

int sum(int p)
{
    int ans = 0;
    for (int i = p; i > 0; i -= low_bit(i))
        ans += c[i];
    return ans;
}

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
        c[i] = 0, a[i] = 1, f[i] = i;

    add(1, n);
    int num = n;
    for (int i = 1; i <= m; ++i)
    {
        int temp;
        scanf("%d", &temp);
        if (!temp)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            x = find_set(x);
            y = find_set(y);
            if (x == y)
                continue;
            add(a[x], -1);
            add(a[y], -1);
            add(a[x] + a[y], 1);
            f[x] = y;
            a[y] += a[x];
            --num;
        }
        else
        {
            int k;
            scanf("%d", &k);
            k = num - k + 1;
            int l = 1, r = n;
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                if (k <= sum(mid))
                    r = mid - 1;
                else 
                    l = mid + 1;
            }
            printf("%d\n", l);
        }
    }
    return 0;
}