
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
#define min(a, b) ((a) < (b) ? (a) : (b))
const int inf = ~0u>>2;

char str[16][32];
int len[16][16]; // len[i][j]用i串的前缀去匹配j串的后缀的最大长度
int le[16];
int dp[1<<15][15];
int p[16];

void getp(const char b[], int m)
{
    int i, j = 0;
    p[1] = 0;
    for (i = 2; i <= m; ++i)
    {
        while (j > 0 && b[j+1] != b[i])
            j = p[j];
        if (b[j+1] == b[i])
            ++j;
        p[i] = j;
    }
}

int kmp(const char a[], int n, const char b[], int m)
{
    int i, j = 0;
    int ans = 0;
    for (i = 1; i <= n; ++i)
    {
        while (j > 0 && b[j+1] != a[i])
            j = p[j];
        if (b[j+1] == a[i])
            ++j;
        ans = j;
        if (j == m)
            j = p[j];
    }
    return ans;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int i, j, n;
        scanf("%d", &n);
        for (i = 0; i < n; ++i)
            scanf("%s", str[i] + 1), le[i] = strlen(str[i]+1);

        memset(len, 0, sizeof(len));
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                memset(p, 0, sizeof(p));
                int temp;
                getp(str[i], le[i]);
                temp = kmp(str[j], le[j], str[i], le[i]);
                if (temp > len[i][j])
                    len[i][j] = temp;
                //printf("%d\n", temp);
            }
        }

        for(i=0;i<(1<<n);i++)//len[i][j]用i串的前缀去匹配j串的后缀的最大长度
        {
            for(j=0;j<n;j++)
            {
                dp[i][j]=inf;
                if(i&(1<<j))
                {
                    if((i^(1<<j)) == 0) dp[i][j]= le[j];
                    else
                    {
                        for(int k=0;k<n;k++)
                        {
                            if((i&(1<<k)) && j!=k)
                            {
                                dp[i][j]=min(dp[i][j],dp[i^(1<<j)][k]+le[j]-len[j][k]);
                            }
                        }
                    }
                }
            }
        }
        int ans=inf;
        for(int i=0;i<n;i++)
            ans=min(ans,dp[(1<<n)-1][i]);
        printf("%d\n",ans);
    }
    return 0;
}
