
#include <iostream>
#include <algorithm>
using namespace std;

#define lhs l, m, rt << 1
#define rhs m + 1, r, rt << 1 | 1

const int maxn = 51000;
int segmax[maxn << 2], segmin[maxn << 2];

struct hInfo {
    int hmax, hmin;
};

void pushUp(int rt)
{
    segmax[rt] = max(segmax[rt << 1], segmax[rt << 1 | 1]);
    segmin[rt] = min(segmin[rt << 1], segmin[rt << 1 | 1]);
}

void update(int p, int value, int l, int r, int rt)
{
    if (l == r)
    {
        segmax[rt] = segmin[rt] = value;
        return ;
    }

    int m = (l + r) >> 1;
    if (p <= m)
        update(p, value, lhs);
    else
        update(p, value, rhs);

    pushUp(rt);
}

void query(hInfo& res, int beg, int end, int l, int r, int rt)
{
    if (beg <= l && r <= end)
    {
        res.hmax = max(res.hmax, segmax[rt]);
        res.hmin = min(res.hmin, segmin[rt]);
        return ;
    }
    
    int m = (l + r) >> 1;
    if (beg <= m)
        query(res, beg, end, lhs);
    if (end > m)
        query(res, beg, end, rhs);
}

int main()
{
    int n, m, h;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &h);
        update(i, h, 1, n, 1);
    }

    for (int i = 0; i < m; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        hInfo info;
        info.hmax = 0, info.hmin = 1000000;
        query(info, a, b, 1, n, 1);

        printf("%d\n", info.hmax - info.hmin);
    }
    return 0;
}