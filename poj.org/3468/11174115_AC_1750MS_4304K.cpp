
#include <cstdio>

#define lhs l, m, rt << 1
#define rhs m + 1, r, rt << 1 | 1

const int maxn = 100010;
long long int seg[maxn << 2];
long long int col[maxn << 2];

void PushUp(int rt)
{
    seg[rt] = seg[rt << 1] + seg[rt << 1 | 1];
}

void PushDown(int rt, int len)
{
    if (col[rt])
    {
        col[rt << 1] += col[rt];
        col[rt << 1 | 1] += col[rt];
        seg[rt << 1] += (len - (len >> 1)) * col[rt];
        seg[rt << 1 | 1] += (len >> 1) * col[rt];
        col[rt] = 0;
    }
}


void Build(int l, int r, int rt)
{
    col[rt] = 0;

    if (l == r)
        scanf("%lld", &seg[rt]);
    else
    {
        int m = (l + r) >> 1;
        Build(lhs);
        Build(rhs);
        PushUp(rt);
    }
}

void Update(int beg, int end, int value, int l, int r, int rt)
{
    if (beg <= l && r <= end)
    {
        col[rt] += value;
        seg[rt] += (r - l + 1) * value;
    }
    else
    {
        PushDown(rt, r - l + 1);
        int m = (l + r) >> 1;
        if (beg <= m)
            Update(beg, end, value, lhs);
        if (end > m)
            Update(beg, end, value, rhs);
        PushUp(rt);
    }
}

long long int Query(int beg, int end, int l, int r, int rt)
{
    if (beg <= l && r <= end)
        return seg[rt];

    PushDown(rt, r - l + 1);

    long long int ret = 0;
    int m = (l + r) >> 1;
    if (beg <= m)
        ret += Query(beg, end, lhs);
    if (end > m)
        ret += Query(beg, end, rhs);

    return ret;
}

int main()
{
    int n, q;
    scanf("%d %d", &n, &q);

    Build(1, n, 1);

    for (int i = 0; i < q; ++i)
    {
        char op[8];
        int a, b, c;
        scanf("%s", op);

        if (op[0] == 'Q')
        {
            scanf("%d %d", &a, &b);
            printf("%lld\n", Query(a, b, 1, n, 1));
        }
        else if (op[0] == 'C')
        {
            scanf("%d %d %d", &a, &b, &c);
            Update(a, b, c, 1, n, 1);
        }
    }
    return 0;
}