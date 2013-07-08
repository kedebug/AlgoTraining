
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAXN = 50010;
int dp1[MAXN], dp2[MAXN], a[MAXN];

int main()
{
    int t, n;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);

        int tmax = -100000;
        int temp = 0;
        
        for (int i = 1; i <= n; ++i)
        {
            temp += a[i];
            if (temp > tmax)
                tmax = temp;
            if (temp < 0)
                temp = 0;
            dp1[i] = tmax;
        }
        tmax = -100000;
        temp = 0;
        for (int i = n; i >= 1; --i)
        {
            temp += a[i];
            if (temp > tmax)
                tmax = temp;
            if (temp < 0)
                temp = 0;
            dp2[i] = tmax;
        }
        int ans = -100000;
        for (int i = 1; i < n; ++i)
            if (ans < dp1[i] + dp2[i+1])
                ans = dp1[i] + dp2[i+1];
        printf("%d\n", ans);
    }
    return 0;
}