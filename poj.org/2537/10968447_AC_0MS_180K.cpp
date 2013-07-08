#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
int main()
{
    int n, k, i, j;
    double dp[103][11];
    while(~scanf("%d%d",&k,&n))
    {
        memset(dp,0,sizeof(dp));
        for(i=1;i<=k+1;i++)
            dp[1][i]=1;
        for(i=2;i<=n;i++)
        {
            for(j=1;j<=k+1;j++)
                dp[i][j]=dp[i-1][j]+dp[i-1][j-1]+dp[i-1][j+1];
        }
        double s=0;
        for(i=1;i<=k+1;i++)
            s+=dp[n][i];
        printf("%.5f\n",s*100/pow(k+1.0,n));
    }
    return 0;
}