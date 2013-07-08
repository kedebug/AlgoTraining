
#include <iostream>
#include <algorithm>
using namespace std;

#define lhs l, m, rt << 1
#define rhs m + 1, r, rt << 1 | 1

const int maxn = 2010;
double sum[maxn << 2];
int cnt[maxn << 2];
double xcord[maxn];

struct Segment {
    double l, r, h;
    int flag;
    Segment() { }
    Segment(double _l, double _r, double _h, int _f) 
        : l(_l), r(_r), h(_h), flag(_f) { }
    bool operator < (Segment& other) { return h < other.h; }
} seg[maxn] ;

void PushUp(int l, int r, int rt)
{
    if (cnt[rt] > 0)
        sum[rt] = xcord[r+1] - xcord[l];
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

int BinSearch(double key, double arr[], int size)
{
    int l = 0, r = size - 1;
    while (l <= r)
    {
        int m = (l + r) >> 1;
        if (arr[m] == key)
            return m;
        else if (arr[m] > key)
            r = m - 1;
        else
            l = m + 1;
    }
    return -1;
}

int main()
{
    int n, m;
    int cases = 0;
    while (~scanf("%d", &n) && n)
    {
        m = 0;
        for (int i = 0; i < n; ++i)
        {
            double a, b, c, d;
            scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
            xcord[m] = a;
            seg[m++] = Segment(a, c, b, 1);
            xcord[m] = c;
            seg[m++] = Segment(a, c, d, -1);
        }
        sort(xcord, xcord + m);
        sort(seg, seg + m);

        int mm = m;
        m = 1;
        for (int i = 1; i < mm; ++i)
            if (xcord[i] != xcord[i-1])
                xcord[m++] = xcord[i];

        memset(cnt, 0, sizeof(cnt));
        memset(sum, 0, sizeof(sum));

        double ret = 0;
        for (int i = 0; i < mm - 1; ++i)
        {
            int l = BinSearch(seg[i].l, xcord, m);
            int r = BinSearch(seg[i].r, xcord, m) - 1;
            if (l <= r)
                Update(l, r, seg[i].flag, 0, m - 1, 1);
            ret += sum[1] * (seg[i+1].h - seg[i].h);
        }
        printf("Test case #%d\nTotal explored area: %.2lf\n\n", ++cases, ret);
    }
    return 0;
}