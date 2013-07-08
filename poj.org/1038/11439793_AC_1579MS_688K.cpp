#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
int n,m,k;
int bad[151][11];
int dp[2][60000];
int stateA[11],stateB[11];
int fact3[11];

void getFact3()
{
    int i;
    for(i=1,fact3[0]=1;i<11;i++)
     fact3[i]=fact3[i-1]*3;
}
int getState(int f[])
{
    int tmp=0,i;
    for(i=m;i>=1;i--)
     tmp *= 3, tmp += f[i];
    return tmp;
}
void backState(int s,int f[])
{
    for(int i=1;i<=10;i++)
    {
        f[i]=s%3;
        s/=3;
    }
}
void init()
{
    memset(dp[1],-1,sizeof(dp[1]));
    memset(stateA,0,sizeof(stateA));
    for(int i=1;i<=m;i++)  //开始我把m写成了10，结果调试了半天
     stateA[i]=bad[1][i]+1;
   dp[1][getState(stateA)]=0;
}
inline int max(int a,int b)
{
    return a>b?a:b;
}
void dfs(int x,int i,int ct,int state)
{
    int now;
    if(i>=m) return;
    if(i<=m-2&&stateA[i]==0&&stateA[i+1]==0&&stateA[i+2]==0) //横放
    {
        stateA[i]=stateA[i+1]=stateA[i+2]=2;
        now=getState(stateA);
        dp[x % 2][now] = max(dp[x % 2][now],ct+1);
        dfs(x,i+3,ct+1,now);
        stateA[i]=stateA[i+1]=stateA[i+2]=0;
    }
    if (stateA[i] == 0 && stateA[i + 1] == 0 && stateB[i] == 0 && stateB[i + 1] == 0)  //竖着放
    {
         stateA[i] = stateA[i + 1] = 2;
         now=getState(stateA);
         dp[x%2][now]=max(dp[x%2][now],ct+1);
         dfs(x,i+2,ct+1,now);
         stateA[i] = stateA[i + 1] = 0;
    }
    dp[x%2][state]=max(dp[x%2][state],dp[(x+1)%2][getState(stateB)]);
    dfs(x,i+1,ct,state); //不放
}

void Dp()
{
    int i,j;
    for(i=2;i<=n;i++)
    {
        memset(dp[i%2],-1,sizeof(dp[i%2]));
        for(j=0;j<fact3[m];j++)
        {
            if(dp[(i+1)%2][j]!=-1)
            {
                backState(j,stateB);
                for(int k=1;k<=m;k++)
                 if(bad[i][k]==1)
                   stateA[k]=2;
                 else
                   {
                       stateA[k] = stateB[k] - 1;
                       if(stateA[k] < 0)
                         stateA[k] = 0;
                   }
                dfs(i,1,dp[(i+1)%2][j],getState(stateA));
            }
        }
    }
}
int solve()
{
    int ans=0,i;
    for(int i=0;i<fact3[m];i++)
     ans=max(ans,max(dp[0][i],dp[1][i]));
    return ans;
}
int main()
{
    int d,i;
    getFact3();
    cin>>d;
    for(i=0;i<d;i++)
    {
        cin>>n>>m>>k;
        int j,x,y;
        memset(bad,0,sizeof(bad));
        for(j=0;j<k;j++)
        {
            cin>>x>>y;
            bad[x][y]=1;
        }
        if(n<2) { puts("0");continue; }
        getFact3();
       // cout<< fact3[10]<<endl;
        init();
        Dp();
        printf("%d\n",solve());
    }
    return 0;
}