#include<stdio.h>
int map[25][25];
int in[25];
int out[25];
int n,ans;
void dfs(int k,int s,int ni,int no)
{
    int i,sum;
    if(s>=ans)
        return;
    sum=0;
    for(i=1;i<=ni;i++)
        sum+=map[in[i]][k];
    if(k==n)
    {
        if(s+sum<ans)
            ans=s+sum;
    }
    else
    {
        in[ni+1]=k;
        dfs(k+1,s+sum,ni+1,no);
    }
    sum=0;
    for(i=1;i<=no;i++)
        sum+=map[out[i]][k];
    if(k==n)
    {
        if(s+sum<ans)
            ans=s+sum;
    }
    else
    {
        out[no+1]=k;
        dfs(k+1,s+sum,ni,no+1);
    }
    return;
}
int main()
{
    int i,j,k,p=0,q=0;
    scanf("%d",&n);
    ans=0;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            scanf("%d",&map[i][j]);
            ans+=map[i][j];
        }
    }
    k=ans/2;
    ans = 0x3fffffff;
    in[1]=1;
    dfs(2,0,1,0);
    printf("%d\n",k-ans);
    return 0;
}