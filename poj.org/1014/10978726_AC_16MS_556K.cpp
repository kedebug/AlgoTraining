
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define max(a,b) (((a) > (b)) ? (a) : (b))

int a[10], dp[100010];
int val;

void cpack(int w, int v)
{
    for (int i = w; i <= val; ++i)
        dp[i] = max(dp[i], dp[i-w] + v);
}

void zpack(int w, int v)
{
    for (int i = val; i >= w; --i)
        dp[i] = max(dp[i], dp[i-w] + v);
}

int main()
{
    int t = 1;
    while (true)
    {
        int sum = 0;
        for (int i = 1; i <= 6; ++i)
            scanf("%d", &a[i]), sum += a[i] * i;
        if (!sum)
            break;
        if (sum & 1)
        {
            printf("Collection #%d:\nCan't be divided.\n\n", t++);
            continue;
        }
        val = sum >> 1;
        memset(dp, 0, sizeof(dp));

        for (int i = 1; i <= 6; ++i)
        {
            if (a[i] * i >= val)
                cpack(i, i);
            else
            {
                int k = 1;
                while (k <= a[i])
                {
                    zpack(k * i, k * i);
                    a[i] -= k;
                    k <<= 1;
                }
                zpack(a[i] * i, a[i] * i);
            }
        }
        if (dp[val] == val)
            printf("Collection #%d:\nCan be divided.\n\n", t++);
        else
            printf("Collection #%d:\nCan't be divided.\n\n", t++);
    }
    return 0;
}