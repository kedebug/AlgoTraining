
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 10010;

typedef struct _Node {
    int px, dx;
    friend bool operator< (const _Node& a, const _Node& b)
    { return a.px > b.px; }
} Node;

Node q[MAXN];
int f[MAXN];

int find(int x)
{
    int r = x;
    while (f[r] != r)
        r = f[r];
    int p = x;
    int q;
    while (p != r)
        q = f[p], f[p] = r, p = q;
    return r;
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        int i, r;
        for (i = 0; i < MAXN; ++i)
            f[i] = i;
        for (i = 0; i < n; ++i)
            scanf("%d %d", &q[i].px, &q[i].dx);
        
        sort(q, q + n);
        int ans = 0;
        for (i = 0; i < n; ++i)
        {
            r = find(q[i].dx);
            if (r > 0)
                f[r] = r - 1, ans += q[i].px;
        }
        printf("%d\n", ans);
    }
    return 0;
}