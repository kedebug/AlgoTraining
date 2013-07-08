
#include <iostream>
#include <algorithm>
using namespace std;

#define lhs l, m, rt << 1
#define rhs m + 1, r, rt << 1 | 1

const int maxn = 200010;
unsigned int sum[maxn << 2], cnt[maxn << 2];

struct Segment {
    unsigned int l, r, h, v;
    Segment() { }

    Segment(int _l, int _r, int _h, int _v) : 
    l(_l), r(_r), h(_h), v(_v) { }

    bool operator < (const Segment& other) 
    { 
        if (h == other.h)
            return v > other.v;
        else
            return h < other.h; 
    }
} seg[maxn << 1] ;

void PushUp(int l, int r, int rt)
{
    if (cnt[rt])
        sum[rt] = r - l + 1;
    else if (l == r)
        sum[rt] = 0;
    else
        sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
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
    while (scanf("%d", &n) && n)
    {
        int m = 0;
        int beg = 50000, end = 0;
        for (int i = 0; i < n; ++i)
        {
            int a, b, c, d;
            int a1, b1, c1, d1;

            scanf("%d %d %d %d", &a, &b, &c, &d);
            scanf("%d %d %d %d", &a1, &b1, &c1, &d1);

            beg = min(beg, a);
            end = max(end, c);

            seg[m++] = Segment(a, a1, b, 1);
            seg[m++] = Segment(a, a1, d, -1);

            seg[m++] = Segment(a1, c1, b, 1);
            seg[m++] = Segment(a1, c1, b1, -1);

            seg[m++] = Segment(a1, c1, d1, 1);
            seg[m++] = Segment(a1, c1, d, -1);

            seg[m++] = Segment(c1, c, b, 1);
            seg[m++] = Segment(c1, c, d, -1);
        }
        sort(seg, seg + m);

        memset(sum, 0, sizeof(sum));
        memset(cnt, 0, sizeof(cnt));

        __int64 ret = 0;
        for (int i = 0; i < m - 1; ++i)
        {
            if (seg[i].l < seg[i].r)
                Update(seg[i].l, seg[i].r - 1, seg[i].v, beg, end - 1, 1);
            ret += (__int64)(sum[1] * (seg[i+1].h - seg[i].h));
        }
        printf("%I64d\n", ret);
    }
    return 0;
}