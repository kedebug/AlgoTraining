
#include <iostream>
#include <algorithm>
using namespace std;

#define lhs l, m, rt << 1
#define rhs m + 1, r, rt << 1 | 1

#define LL long long int 

const int maxn = 30010;
int segmax[maxn << 2], lab[maxn << 2];
LL xcord[maxn];

struct Star {
    LL x, y;
    int value;

    Star() { }
    Star(LL _x, LL _y, int _v) 
        : x(_x), y(_y), value(_v) { }

    bool operator < (const Star& other)
    { return y < other.y; }
} star[maxn] ;

void pushUp(int rt)
{
    segmax[rt] = max(segmax[rt << 1], segmax[rt << 1 | 1]);
}

void pushDown(int rt)
{
    if (lab[rt])
    {
        lab[rt << 1] += lab[rt];
        lab[rt << 1 | 1] += lab[rt];
        segmax[rt << 1] += lab[rt];
        segmax[rt << 1 | 1] += lab[rt];
        lab[rt] = 0;
    }
}

void update(int beg, int end, int value, int l, int r, int rt)
{
    if (beg <= l && r <= end)
    {
        lab[rt] += value;
        segmax[rt] += value;
        return ;
    }
    pushDown(rt);

    int m = (l + r) >> 1;
    if (beg <= m)
        update(beg, end, value, lhs);
    if (end > m)
        update(beg, end, value, rhs);

    pushUp(rt);
}

int main()
{
    int n, W, H;
    while (scanf("%d %d %d", &n, &W, &H) != EOF)
    {
        int m = 0, ret = 0;
        for (int i = 0; i < n; ++i)
        {
            scanf("%lld %lld %d", &star[i].x, &star[i].y, &star[i].value);
            xcord[m++] = star[i].x;
            xcord[m++] = star[i].x + W;
        }
        sort(xcord, xcord + m);
        sort(star, star + n);

        m = unique(xcord, xcord + m) - xcord;

        memset(segmax, 0, sizeof(segmax));
        memset(lab, 0, sizeof(lab));

        for (int i = 0, j = 0; i < n; ++i)
        {
            int beg = lower_bound(xcord, xcord + m, star[i].x) - xcord;
            int end = lower_bound(xcord, xcord + m, star[i].x + W) - xcord - 1;
            update(beg, end, star[i].value, 0, m - 1, 1);

            while (j <= i && star[i].y - star[j].y >= H)
            {
                beg = lower_bound(xcord, xcord + m, star[j].x) - xcord;
                end = lower_bound(xcord, xcord + m, star[j].x + W) - xcord - 1;
                update(beg, end, -star[j++].value, 0, m - 1, 1);
            }

            ret = max(ret, segmax[1]);
        }
        printf("%d\n", ret);
    }
    return 0;
}