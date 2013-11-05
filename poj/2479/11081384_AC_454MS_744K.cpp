
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>

const int MAXN = 50010;
int an[MAXN];
int d1[MAXN], d2[MAXN];

int main()
{
    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        int n;
        scanf("%d", &n);

        for (int i = 1; i <= n; ++i)
            scanf("%d", &an[i]);

        int tmax = INT_MIN, temp = 0;
        for (int i = 1; i <= n; ++i)
        {
            temp += an[i];
            if (tmax < temp)
                tmax = temp;
            if (temp < 0)
                temp = 0;
            d1[i] = tmax;
        }
        tmax = INT_MIN, temp = 0;
        for (int i = n; i >= 1; --i)
        {
            temp += an[i];
            if (tmax < temp)
                tmax = temp;
            if (temp < 0)
                temp = 0;
            d2[i] = tmax;
        }

        int ans = INT_MIN;
        for (int i = 1; i < n; ++i)
            if (ans < d1[i] + d2[i+1])
                ans = d1[i] + d2[i+1];

        printf("%d\n", ans);
    }
	return 0;
}