
#include <cstdio>

#define lhs l, m, rt << 1
#define rhs m + 1, r, rt << 1 | 1

const int maxn = 200010;
int seq[maxn << 2];
int pos[maxn], val[maxn], order[maxn];

void PushUp(int rt)
{
    seq[rt] = seq[rt << 1] + seq[rt << 1 | 1];
}

void Build(int l, int r, int rt)
{
    if (l == r)
        seq[rt] = 1;
    else
    {
        int m = (l + r) >> 1;
        Build(lhs);
        Build(rhs);
        PushUp(rt);
    }
}

void Query(int p, int value, int l, int r, int rt)
{
    if (l == r)
    {
        seq[rt] = 0;
        order[l] = value;
    }
    else
    {
        int m = (l + r) >> 1;
        if (seq[rt << 1] > p)
            Query(p, value, lhs);
        else
            Query(p - seq[rt << 1], value, rhs);
        PushUp(rt);
    }
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 0; i < n; ++i)
            scanf("%d %d", &pos[i], &val[i]);

        Build(0, n - 1, 1);
        for (int i = n - 1; i >= 0; --i)
            Query(pos[i], val[i], 0, n - 1, 1);

        printf("%d", order[0]);
        for (int i = 1; i < n; ++i)
            printf(" %d", order[i]);
        printf("\n");
    }
    return 0;
}