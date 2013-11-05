
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int nMax = 100;
const int mMax = 100050;

#define max(a,b)    (((a) > (b)) ? (a) : (b))

int main()
{
    int cash, t;
    int val[nMax];
    int dp[mMax];
    while (scanf("%d %d", &cash, &t) != EOF)
    {
        int c;
        int n, v, i, k;

        memset(val, 0, sizeof(val));
        memset(dp, 0, (cash + 10) * sizeof(int));

        c = 0;
        while (t--)
        {
            scanf("%d %d", &n, &v);
            k = 1; 
            while (n - k >= 0)
            {
                val[c++] = v * k;
                n -= k;
                k *= 2;
            }
            if (n)
                val[c++] = v * n;
        }
        // dp[0] = 1;
        for (i = 0; i < c; ++i)
            for (k = cash; k >= val[i]; --k)
                dp[k] = max(dp[k], dp[k-val[i]] + val[i]);

        //while (!dp[cash])
          //  --cash;
        printf("%d\n", dp[cash]);
    }
    return 0;
}