#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<queue>
#include<algorithm>
#include<vector>
#include<stack>
#include<list>
#include<iostream>
#include<map>
using namespace std;
#define inf 0x3f3f3f3f
#define Max 110
int max(int a,int b)
{
	return a>b?a:b;
}
int min(int a,int b)
{
	return a<b?a:b;
}
int dp[1<<15][16];
int x1[16],x2[16],y1[16],y2[16],co[16],mp[16];
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,i,j,k,tmp;
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            scanf("%d%d%d%d%d",&y1[i],&x1[i],&y2[i],&x2[i],&co[i]);
        }
        memset(mp,0,sizeof(mp));
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(y2[j]!=y1[i]||x2[j]<=x1[i]||x1[j]>=x2[i])
                    continue;
                mp[i]+=(1<<j);
            }
        }
       // for(i=0;i<(1<<n);i++)
         //   dp[i][0]=0;
        for(i=0;i<(1<<n);i++)
            for(j=0;j<n;j++)
            {

                dp[i][j]=inf;
                if((i&(1<<j))!=0&&((i&mp[j])==mp[j]))
                {
                    tmp=i-(1<<j);
                    if(tmp==0)
                    {
                        dp[i][j]=1;
                        continue;
                    }
                    for(k=0;k<n;k++)
                    {
                        if((tmp&(1<<k))!=0&&((tmp&mp[k])==mp[k])&&dp[tmp][k]!=inf)
                        {
                            if(co[k]==co[j])
                            dp[i][j]=min(dp[i][j],dp[tmp][k]);
                            else
                            dp[i][j]=min(dp[i][j],dp[tmp][k]+1);
                        }
                    }
                }
            }
            int ans=inf;
            for(i=0;i<n;i++)
            {
                ans=min(ans,dp[(1<<n)-1][i]);
            }
            printf("%d\n",ans);
    }
}
