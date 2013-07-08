
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

#define lhs l, m, rt << 1
#define rhs m + 1, r, rt << 1 | 1

const int mix = -1;
const int maxn = 8010;
int color[maxn << 3];
int lab[maxn];

vector<int> map[maxn];

struct seg {
    int l, r, x;
    friend bool operator < (const seg& s1, const seg& s2) { return s1.x < s2.x; }
} seg[maxn] ;

void PushDown(int rt)
{
    if (color[rt] != mix)
    {
        color[rt << 1] = color[rt << 1 | 1] = color[rt];
        color[rt] = mix;
    }
}

void Update(int beg, int end, int value, int l, int r, int rt)
{
    if (beg <= l && r <= end)
    {
        color[rt] = value;
        return ;
    }
    PushDown(rt);

    int m = (l + r) >> 1;
    if (beg <= m)
        Update(beg, end, value, lhs);
    if (end > m)
        Update(beg, end, value, rhs);
}

void Query(int beg, int end, int value, int l, int r, int rt)
{
    if (color[rt] != mix)
    {
        if (lab[color[rt]] != value)
        {
            map[value].push_back(color[rt]);
            lab[color[rt]] = value;
        }
        return ;
    }
    if (l == r)
        return ;

    PushDown(rt);

    int m = (l + r) >> 1;
    if (beg <= m)
        Query(beg, end, value, lhs);  
    if (end > m)
        Query(beg, end, value, rhs);
}

int main()
{
    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        int a, b, c, n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d %d", &a, &b, &c);
            seg[i].l = a * 2;
            seg[i].r = b * 2;
            seg[i].x = c;
            map[i].clear();
        }

        sort(seg, seg + n);

        memset(color, -1, sizeof(color));
        memset(lab, -1, sizeof(lab));

        for (int i = 0; i < n; ++i)
        {
            Query(seg[i].l, seg[i].r, i, 0, maxn << 1, 1);
            Update(seg[i].l, seg[i].r, i, 0, maxn << 1, 1);
        }

        int ret = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < map[i].size(); ++j)
            {
                int t = map[i][j];
                for (int k = 0; k < map[i].size(); ++k)
                    for (int m = 0; m < map[t].size(); ++m)
                        if (map[i][k] == map[t][m])
                            ++ret;
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}