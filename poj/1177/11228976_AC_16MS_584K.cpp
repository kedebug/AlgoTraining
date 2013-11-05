
#include <iostream>
#include <algorithm>
using namespace std;

#define lhs l, m, rt << 1
#define rhs m + 1, r, rt << 1 | 1

const int maxn = 20010;
int xsum[maxn << 2], ynum[maxn << 2];
int cnt[maxn << 2];
bool lbd[maxn << 2], rbd[maxn << 2];

struct Segment {
    int l, r, h, v;
    Segment() { }
    Segment(int _l, int _r, int _h, int _v) : l(_l), r(_r), h(_h), v(_v) { }
    bool operator < (const Segment& other) { return h < other.h; }
} seg[maxn] ;

void PushUp(int l, int r, int rt)
{
    if (cnt[rt])
    {
        lbd[rt] = rbd[rt] = true;
        xsum[rt] = r - l + 1;
        ynum[rt] = 2;
    }
    else if (l == r)
    {
        lbd[rt] = rbd[rt] = false;
        xsum[rt] = ynum[rt] = 0;
    }
    else
    {
        lbd[rt] = lbd[rt << 1];
        rbd[rt] = rbd[rt << 1 | 1];
        xsum[rt] = xsum[rt << 1] + xsum[rt << 1 | 1];
        ynum[rt] = ynum[rt << 1] + ynum[rt << 1 | 1];

        if (lbd[rt << 1 | 1] && rbd[rt << 1])
            ynum[rt] -= 2;
    }
}

void Update(int beg, int end, int value, int l, int r, int rt)
{
    if (beg <= l && r <= end)
    {
        cnt[rt] += value;
        PushUp(l, r, rt);
        return ;
    }
    int m = (l + r) >> 1;
    if (beg <= m)
        Update(beg, end, value, lhs);
    if (end > m)
        Update(beg, end, value, rhs);
    PushUp(l, r, rt);
}

int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        int m = 0;
        int beg = 10000, end = -10000;
        for (int i = 0; i < n; ++i)
        {
            int a, b, c, d;
            scanf("%d %d %d %d", &a, &b, &c, &d);
            beg = min(a, beg);
            end = max(c, end);
            seg[m++] = Segment(a, c, b, 1);
            seg[m++] = Segment(a, c, d, -1);
        }
        sort(seg, seg + m);
        
        int ret = 0, pre = 0;
        for (int i = 0; i < m; ++i)
        {
            if (seg[i].l < seg[i].r)
                Update(seg[i].l, seg[i].r - 1, seg[i].v, beg, end - 1, 1);
            ret += abs(xsum[1] - pre);
            pre = xsum[1];
            ret += ynum[1] * (seg[i+1].h - seg[i].h);
        }
        printf("%d\n", ret);
    }
    return 0;
}