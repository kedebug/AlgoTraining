
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define lhs l, m, rt << 1
#define rhs m + 1, r, rt << 1 | 1

const int maxn = 200010;

typedef struct _Point {
    int x, y;
    bool operator < (const _Point& other)
    { return x < other.x; }
} Coord ;

class CSegTree
{
private:
    int sum[maxn << 2];
public:
    void pushUp(int rt)
    {
        sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    }
    void build(int l, int r, int rt)
    {
        sum[rt] = 0;
        if (l == r)
            return ;
        int m = (l + r) >> 1;
        build(lhs);
        build(rhs);
    }
    void update(int p, int value, int l, int r, int rt)
    {
        if (l == r)
        {
            sum[rt] += value;
            return ;
        }
        int m = (l + r) >> 1;
        if (p <= m)
            update(p, value, lhs);
        else
            update(p, value, rhs);
        pushUp(rt);
    }
    int query(int beg, int end, int l, int r, int rt)
    {
        if (beg <= l && r <= end)
            return sum[rt];
        int m = (l + r) >> 1;
        int ret = 0;
        if (beg <= m)
            ret += query(beg, end, lhs);
        if (end > m)
            ret += query(beg, end, rhs);
        return ret;
    }
};

CSegTree ltree, rtree;
Coord cord[maxn];
int ycord[maxn];

int binSearch(int value, int arr[], int size)
{
    return lower_bound(arr, arr + size, value) - arr;
}

int main()
{
    int n;
    while (scanf("%d", &n) && n)
    {
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d", &cord[i].x, &cord[i].y);
            ycord[i+1] = cord[i].y;
        }
        sort(ycord + 1, ycord + n + 1);
        sort(cord, cord + n);

        int m = unique(ycord + 1, ycord + n + 1) - (ycord + 1);

        ltree.build(0, m, 1);
        rtree.build(0, m, 1);

        int p;
        for (int i = 0; i < n; ++i)
        {
            p = binSearch(cord[i].y, ycord + 1, m) + 1;
            rtree.update(p, 1, 0, m, 1);
        }

        int best = 0;
        vector<int> ret;
        for (int i = 1, s = 0; i <= n; ++i)
        {
            if (i == n || cord[i].x != cord[i-1].x)
            {
                for (int j = s; j < i; ++j)
                {
                    p = binSearch(cord[j].y, ycord + 1, m) + 1;
                    rtree.update(p, -1, 0, m, 1);
                }

                int ollie = -1, stan = -1;
                for (int j = s; j < i; ++j)
                {
                    p = binSearch(cord[j].y, ycord + 1, m) + 1;
                    int a = ltree.query(0, p - 1, 0, m, 1) + rtree.query(p + 1, m, 0, m, 1);
                    int b = rtree.query(0, p - 1, 0, m, 1) + ltree.query(p + 1, m, 0, m, 1);

                    if (ollie == b)
                        stan = min(stan, a);
                    else if (ollie < b)
                        ollie = b, stan = a;
                }
                if (stan == best)
                    ret.push_back(ollie);
                else if (stan > best)
                    best = stan, ret.clear(), ret.push_back(ollie);
                
                for (int j = s; j < i; ++j)
                {
                    p = binSearch(cord[j].y, ycord + 1, m) + 1;
                    ltree.update(p, 1, 0, m, 1);
                }

                s = i;
            }
        }
        sort(ret.begin(), ret.end());

        printf("Stan: %d; Ollie:", best);

        for (int i = 0; i < ret.size(); ++i)
            if (i == 0 || ret[i] != ret[i-1])
                printf(" %d", ret[i]);
        
        printf(";\n");
    }
    return 0;
}
