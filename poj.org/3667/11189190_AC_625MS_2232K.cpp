
#include <cstdio>
#include <algorithm>
using namespace std;

#define lhs l, m, rt << 1
#define rhs m + 1, r, rt << 1 | 1

const int maxn = 50010;
int sum[maxn << 2], lab[maxn << 2];
int lsum[maxn << 2], rsum[maxn << 2];

enum __check { checkout = 0, checkin };

void PushDown(int rt, int m)
{
    if (lab[rt] != -1)
    {
        lab[rt << 1] = lab[rt << 1 | 1] = lab[rt];
        sum[rt << 1] = lsum[rt << 1] = rsum[rt << 1] = lab[rt] ? 0 : m - (m >> 1);
        sum[rt << 1 | 1] = lsum[rt << 1 | 1] = rsum[rt << 1 | 1] = lab[rt] ? 0 : (m >> 1);
        lab[rt] = -1;
    }
}

void PushUp(int rt, int m)
{
    lsum[rt] = lsum[rt << 1];
    rsum[rt] = rsum[rt << 1 | 1];

    if (lsum[rt] == m - (m >> 1))
        lsum[rt] += lsum[rt << 1 | 1];
    if (rsum[rt] == m >> 1)
        rsum[rt] += rsum[rt << 1];

    sum[rt] = max(rsum[rt << 1] + lsum[rt << 1 | 1], max(sum[rt << 1], sum[rt << 1 | 1]));
}

void Build(int l, int r, int rt)
{
    sum[rt] = lsum[rt] = rsum[rt] = r - l + 1;
    lab[rt] = -1;
    if (l == r)
        return ;
    int m = (l + r) >> 1;
    Build(lhs);
    Build(rhs);
}

void Update(int beg, int end, __check c, int l, int r, int rt)
{
    if (beg <= l && r <= end)
    {
        sum[rt] = lsum[rt] = rsum[rt] = c ? 0 : r - l + 1;
        lab[rt] = c;
        return ;
    }
    PushDown(rt, r - l + 1);

    int m = (l + r) >> 1;
    if (beg <= m)
        Update(beg, end, c, lhs);
    if (end > m)
        Update(beg, end, c, rhs);

    PushUp(rt, r - l + 1);
}

int Query(int w, int l, int r, int rt)
{
    if (l == r)
        return r;

    PushDown(rt, r - l + 1);

    int m = (l + r) >> 1;
    if (sum[rt << 1] >= w)
        return Query(w, lhs);
    else if (rsum[rt << 1] + lsum[rt << 1 | 1] >= w)
        return m - rsum[rt << 1] + 1;
    else
        return Query(w, rhs);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    Build(1, n, 1);

    for (int i = 0; i < m; ++i)
    {
        int op, a, b;
        scanf("%d", &op);

        if (op == 1)
        {
            scanf("%d", &a);
            if (sum[1] >= a)
            {
                int p = Query(a, 1, n, 1);
                printf("%d\n", p);
                Update(p, p + a - 1, checkin, 1, n, 1);
            }
            else
                printf("0\n");
        }
        else if (op == 2)
        {
            scanf("%d %d", &a, &b);
            Update(a, a + b - 1, checkout, 1, n, 1);
        }
    }
    return 0;
}