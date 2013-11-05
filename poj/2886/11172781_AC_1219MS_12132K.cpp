
#include <cstdio>

#define lhs l, m, rt << 1
#define rhs m + 1, r, rt << 1 | 1

const int maxn = 500010;

struct _Joseph {
    char name[12];
    int value;
} boy[maxn];

int seg[maxn << 2];

void PushUp(int rt)
{
    seg[rt] = seg[rt << 1] + seg[rt << 1 | 1];
}

void Build(int l, int r, int rt)
{
    if (l == r)
        seg[rt] = 1;
    else
    {
        int m = (l + r) >> 1;
        Build(lhs);
        Build(rhs);
        PushUp(rt);
    }
}

int Update(int delta, int l, int r, int rt)
{
    int ret;
    if (l == r)
    {
        seg[rt] = 0;
        ret = r;
    }
    else
    {
        int m = (l + r) >> 1;
        if (delta <= seg[rt << 1])
            ret = Update(delta, lhs);
        else
            ret = Update(delta - seg[rt << 1], rhs);
        PushUp(rt);
    }
    return ret;
}

const int antiprime[] = {
    1,2,4,6,12,24,36,48,60,120,180,240,360,
    720,840,1260,1680,2520,5040,7560,10080,15120,20160,25200,
    27720,45360,50400,55440,83160,110880,166320, 221760, 
    277200, 332640, 498960, 554400, 665280};
const int factorNum[] = {
    1, 2, 3, 4, 6, 8, 9, 10, 12, 16, 18, 20, 
    24, 30, 32, 36, 40, 48, 60, 64, 72, 80, 84, 
    90, 96, 100, 108, 120, 128, 144, 160, 168, 180, 192, 200, 216, 224};

int main()
{
    int n, k;

    while (~scanf("%d %d", &n, &k))
    {
        for (int i = 1; i <= n; ++i)
            scanf("%s %d", boy[i].name, &boy[i].value);

        Build(1, n, 1);

        int i = 0;
        while (antiprime[i] <= n)
            ++i;

        int times = antiprime[--i];

        int pos = 0;
        boy[pos].value = 0;

        while (times--)
        {
            int mod = seg[1];
            if (boy[pos].value > 0)
                k = ((k + boy[pos].value - 2) % mod + mod) % mod + 1;
            else 
                k = ((k + boy[pos].value - 1) % mod + mod) % mod + 1;
            pos = Update(k, 1, n, 1);
        }

        printf("%s %d\n", boy[pos].name, factorNum[i]);
    }
    return 0;
}
