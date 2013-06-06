#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define lhs l, m, rt << 1
#define rhs m + 1, r, rt << 1 | 1

const int maxn = 200010;
int seg[maxn << 2];

void pushUp(int rt)
{
    seg[rt] = max(seg[rt << 1], seg[rt << 1 | 1]);
}

void build(int l, int r, int rt)
{
    if (l == r)
    {
        scanf("%d", &seg[rt]);
        return;
    }
    int m = (l + r) >> 1;
    build(lhs);
    build(rhs);
    pushUp(rt);
}

void update(int p, int delta, int l, int r, int rt)
{
    if (l == r)
    {
        seg[rt] = delta;
        return;
    }
    int m = (l + r) >> 1;
    if (p <= m)
        update(p, delta, lhs);
    else
        update(p, delta, rhs);
    pushUp(rt);
}

int query(int beg, int end, int l, int r, int rt)
{
    if (beg <= l && r <= end)
        return seg[rt];

    int m = (l + r) >> 1;
    int ret = 0;

    if (beg <= m)
        ret = query(beg, end, lhs);
    if (end > m)
        ret = max(ret, query(beg, end, rhs));

    return ret;
}

int main()
{
    int n, m;
    while (scanf("%d %d", &n, &m) != EOF)
    {
        build(1, n, 1);

        while (m--)
        {
            char op[16];
            int a, b;
            scanf("%s", op);
            scanf("%d %d", &a, &b);

            if (op[0] == 'Q')
                printf("%d\n", query(a, b, 1, n, 1));
            else if (op[0] == 'U')
                update(a, b, 1, n, 1);
        }
    }
    return 0;
}