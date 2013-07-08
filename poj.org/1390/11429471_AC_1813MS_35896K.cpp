#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 209;
int dp[N][N][N];
int re[N];
int dfs(int l,int r,int k)
{
    if(l>r) return 0;
    if(dp[l][r][k]) return dp[l][r][k];
    dp[l][r][k] = dfs(l,r-1,0)+(1+k)*(1+k);
    for(int i=r-1;i>=l;i--)
    if(re[r]==re[i]){
        dp[l][r][k] = max(dp[l][r][k],dfs(l,i,k+1)+dfs(i+1,r-1,0));
    }
    return dp[l][r][k];
}
int main()
{
    int cas,T=1,n;
    scanf("%d",&cas);
    while(cas--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        scanf("%d",&re[i]);
        memset(dp,0,sizeof(dp));
        printf("Case %d: %d\n",T++,dfs(1,n,0));
    }
    return 0;
}
