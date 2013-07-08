#include <stdio.h>
#include <string.h>
#define MAX 2100
#define INF 0xfffffff
#define min(a,b) (a)<(b)?(a):(b)


int state[MAX],dp[MAX];
int n,m1,m2,ans,tot,cost[MAX];


int Ok(int x) {

    int i,j,k,sum = 0;
    int  vis[MAX];


    memset(vis,0,sizeof(vis));
    for (vis[0] = 1,i = 0; i < n; ++i)
    {
        if ((1<<i) & x) 
        {
            sum += cost[i];
            for (j = m1; j >= cost[i]; --j)
                if (vis[j-cost[i]]) 
                    vis[j] = 1;
        }
    }

    for (i = 0; i <= m1; ++i)
        if (vis[i] && sum - i <= m2) 
            return 1;
        return 0;
}


int main()
{
    int i,j,k,t,cas = 0;


    scanf("%d",&t);
    while (t--) {

        scanf("%d%d%d",&n,&m1,&m2);
        for (i = 0; i < n; ++i)
            scanf("%d",&cost[i]);	


        for (i = 0; i < 1<<n; ++i) dp[i] = INF;
        dp[0] = tot = ans = 0;
        for (i = 1; i <= (1<<n) - 1; ++i)
            if (Ok(i)) state[tot++] = i;


        for (i = 0; i < tot; ++i)
            for (j = (1<<n)-1; j >= 0; --j) {

                if (dp[j] == INF) continue;
                int tp = j + state[i];
                if (tp != (j | state[i])) continue;
                dp[tp] = min(dp[tp],dp[j]+1);
            }


            printf("Scenario #%d:\n%d\n\n",++cas,dp[(1<<n)-1]);
    }
}