
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define lhs l, m, rt << 1
#define rhs m + 1, r, rt << 1 | 1

const int maxn = 10010;
int seg[maxn << 4];
int coord[maxn << 2];
int cl[maxn], cr[maxn];
bool hash[maxn];

void PushDown(int rt)
{
    if (seg[rt])
    {
        seg[rt << 1] = seg[rt << 1 | 1] = seg[rt];
        seg[rt] = 0;
    }
}

void Update(int beg, int end, int value, int l, int r, int rt)
{
    if (beg <= l && r <= end)
    {
        seg[rt] = value;
        return ;
    }

    PushDown(rt);
    int m = (l + r) >> 1;
    if (beg <= m)
        Update(beg, end, value, lhs);
    if (end > m)
        Update(beg, end, value, rhs);
}

int Query(int l, int r, int rt)
{
    if (seg[rt] && !hash[seg[rt]])
    {
        hash[seg[rt]] = true;
        return 1;
    }
    else if (seg[rt] || l == r)
        return 0;

    int ret = 0;
    int m = (l + r) >> 1;
    ret += Query(lhs);
    ret += Query(rhs);
    
    return ret;
}

int Search(int l, int r, int value)
{
    while (l <= r)
    {
        int m = (l + r) >> 1;
        if (coord[m] == value)
            return m;
        else if (coord[m] > value)
            r = m - 1;
        else 
            l = m + 1;
    }
    return -1;
}

int main()
{
    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        memset(seg, 0, sizeof(seg));
        memset(coord, 0, sizeof(coord));
        memset(hash, false, sizeof(hash));

        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d %d", &cl[i], &cr[i]);

        int c = 0;
        for (int i = 1; i <= n; ++i)
            coord[++c] = cl[i], coord[++c] = cr[i];

        sort(coord + 1, coord + c + 1);

        int i, j;
        for (i = 1, j = 2; j <= c; ++j)
            if (coord[i] != coord[j])
                coord[++i] = coord[j];

        int m = c = i;
        for (i = 1; i + 1 <= m; ++i)
            if (coord[i] + 1 != coord[i+1])
                coord[++c] = coord[i] + 1;

        sort(coord + 1, coord + c + 1);

        for (int i = 1; i <= n; ++i)
        {
            int a = Search(1, c, cl[i]);
            int b = Search(1, c, cr[i]);
            Update(a, b, i, 1, c, 1);
        }

        printf("%d\n", Query(1, c, 1));
    }
    return 0;
}