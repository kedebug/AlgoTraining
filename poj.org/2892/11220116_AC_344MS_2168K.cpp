
#include <iostream>
#include <stack>
using namespace std;

#define lhs l, m, rt << 1
#define rhs m + 1, r, rt << 1 | 1

const int maxn = 50010;
int sum[maxn << 2], lsum[maxn << 2], rsum[maxn << 2];

void PushUp(int rt, int m)
{
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    lsum[rt] = lsum[rt << 1];
    rsum[rt] = rsum[rt << 1 | 1];

    if (lsum[rt] == m - (m >> 1))
        lsum[rt] += lsum[rt << 1 | 1];
    if (rsum[rt] == m >> 1)
        rsum[rt] += rsum[rt << 1];
}

void Build(int l, int r, int rt)
{
    sum[rt] = lsum[rt] = rsum[rt] = r - l + 1;

    if (l == r)
        return ;

    int m = (l + r) >> 1;
    Build(lhs);
    Build(rhs);
}

void Update(int p, int value, int l, int r, int rt)
{
    if (l == r)
    {
        sum[rt] = lsum[rt] = rsum[rt] = value;
        return ;
    }

    int m = (l + r) >> 1;
    if (p <= m)
        Update(p, value, lhs);
    else
        Update(p, value, rhs);
    PushUp(rt, r - l + 1);
}

int Query(int p, int l, int r, int rt)
{
    if (l == r)
        return sum[rt];

    int m = (l + r) >> 1;
    if (p <= m)
    {
        if (p + rsum[rt << 1] > m)
            return rsum[rt << 1] + lsum[rt << 1 | 1];
        else
            return Query(p, lhs);
    }
    else
    {
        if (m + lsum[rt << 1 | 1] >= p)
            return rsum[rt << 1] + lsum[rt << 1 | 1];
        else
            return Query(p, rhs);
    }
}

int main()
{
    int n, m;
    stack<int> num;

    scanf("%d %d", &n, &m);
    Build(1, n, 1);

    for (int i = 0; i < m; ++i)
    {
        char op[12];
        int x;
        scanf("%s", op);

        if (op[0] == 'D')
        {
            scanf("%d", &x);
            num.push(x);
            Update(x, 0, 1, n, 1);
        }
        else if (op[0] == 'R')
        {
            if (!num.empty())
            {
                Update(num.top(), 1, 1, n, 1);
                num.pop();
            }
        }
        else if (op[0] == 'Q')
        {
            scanf("%d", &x);
            printf("%d\n", Query(x, 1, n, 1));
        }
    }
    return 0;
}