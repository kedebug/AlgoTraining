#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int inf = 100000000;
int box[510][1010];
int map[510][510];
int n,d;
bool ok;
int count=0;
bool solve(int a,int b)
{
    int i,j;
    bool flag=true;
    for(i=1;i<=d;i++)
    {
        if(box[a][i]>=box[b][i])
        {
            flag=false;
            break;
        }
    }
    return flag;
}
void init()
{
    int i,j;
     memset(map,0,sizeof(map));
     for(i=2;i<=n;i++)
     {
         if(solve(1,i)) 
         {
             map[1][i]=1;
             ok=true;
         }
     }
     for(i=2;i<=n;i++)
     {
         for(j=2;j<=n;j++)
         {
             if(solve(i,j))
             {
                 map[i][j]=1;
             }
         }
     }
}
int dp[510];
int main()
{
    int i,j,k;
    while(scanf("%d%d",&n,&d)!=EOF)
    {
        n++;
        ok=false;
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=d;j++)
            {
                scanf("%d",&box[i][j]);
                
            }sort(box[i]+1,box[i]+1+d);
        }
        init();
        if(!ok)
        {
            printf("Please look for another gift shop!");
            continue;
        }
        dp[1]=0;
        for(i=2;i<=n;i++)
            dp[i]=-1;
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=n;j++)
            {
                if(map[i][j]&&dp[i]!=-1)
                {
                    if(dp[i]+1>dp[j])
                    {
                        dp[j]=dp[i]+1;
                    }
                }
            }
        }
        int ans=0;
        for(i=1;i<=n;i++)
        {
            if(dp[i]>ans)
                ans=dp[i];
        }
        printf("%d\n",ans);
    }
    return 0;
}