#include <iostream>
using namespace std;
#define max(a,b) ((a)>(b)?(a):(b))
char dyna[100010];
int dqueue[100010], pl[100010], head, tail;
int w[110], s[110], n, m;
int main ()
{
    int i, j, k, l, maxi, ans;
    while (1)
    {
        scanf("%d %d", &n, &m);
        if (n == 0 && m == 0) break;
        for (i = 1; i <= n; i++)
            scanf("%d", &w[i]);
        for (i = 1; i <= n; i++)
            scanf("%d", &s[i]);
        memset(dyna, 0, sizeof(dyna));
        dyna[0] = 1;
        for (i = 1; i <= n; i++)
        {
            maxi = w[i] * s[i];
            if (s[i] == 1)
            {
                for (j = m; j >= w[i]; j--)
                    dyna[j] = max(dyna[j], dyna[j - w[i]]);
            }
            else if (maxi < m)
            {
                for (j = 0; j < w[i]; j++)
                {
                    head = tail = 0;
                    for (k = j; k <= m; k += w[i])
                    {
                        if (tail != head) { if (k - pl[head] > maxi) head++; }
                        if (dyna[k])
                        {
                            dqueue[tail] = dyna[k];
                            pl[tail] = k; tail++;
                        }
                        else if (tail != head) dyna[k] = 1;
                    }
                }
            }
            else
            {
                for (j = w[i]; j <= m; j++)
                    dyna[j] = max(dyna[j], dyna[j - w[i]]);
            }
        }
        ans = 0;
        for (i = 1; i <= m; i++)
            if (dyna[i]) ans++;
        printf("%d\n", ans);
    }
    return 0;
}