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
#define inf 0x3f3f3f3f3f3f3f3fLL
#define Max 110
int max(int a,int b)
{
	return a>b?a:b;
}
__int64 min(__int64 a,__int64 b)
{
	return a<b?a:b;
}
struct node
{
    int l,r;
    __int64 minx;
    int mid()
    {
        return (l+r)>>1;
    }
}T[4*101000];
int lef[101000],q[101000],a[101000];
__int64 rec;
__int64 sum[101000],dp[101000];
int n;
__int64 m;
void build(int l,int r,int rt)
{
    T[rt].l=l,T[rt].r=r;
    T[rt].minx=inf;
    if(l==r)
        return ;
    int mid=T[rt].mid();
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
}
void modify(int x,int rt,__int64 data)
{
    if(T[rt].l==T[rt].r)
    {
        T[rt].minx=data;
        return;
    }
    int mid=T[rt].mid();
    if(x<=mid)
        modify(x,rt<<1,data);
    else
        modify(x,rt<<1|1,data);
    T[rt].minx=min(T[rt<<1].minx,T[rt<<1|1].minx);
}
void query(int l,int r,int rt)
{
    if(l==T[rt].l&&r==T[rt].r)
    {
        rec=min(rec,T[rt].minx);
        return;
    }
    int mid=T[rt].mid();
    if(r<=mid)
        query(l,r,rt<<1);
    else if(l>=mid+1)
        query(l,r,rt<<1|1);
    else
        {
            query(mid+1,r,rt<<1|1);
            query(l,mid,rt<<1);
        }
}
int main()
{
    int i,j;
    while(scanf("%d%I64d",&n,&m)!=EOF)
    {
        sum[0]=0;
        dp[0]=0;
        j=0;
        int flag=0;
        for(i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            if(a[i]>m)
                flag=1;
            sum[i]=sum[i-1]+a[i];
            for(;j<i;j++)
            {
                if(sum[j]+m>=sum[i])
                {
                    lef[i]=j;
                  //  printf("i %d le %d ",i,lef[i]);
                    break;
                }
            }
        }
        if(flag)
        {
            printf("-1\n");
            continue;
        }
        build(0,n+10,1);
        int top=0,tail=0;
        q[tail++]=0;
       // modify(0,1,0);
        for(i=1;i<=n;i++)
        {
            dp[i]=inf;
            while(tail>top&&a[i]>=a[q[tail-1]])
            {
                modify(q[tail-1],1,inf);
                tail--;
            }
            if(tail>top)
                modify(q[tail-1],1,dp[q[tail-1]]+a[i]);
            q[tail++]=i;
            while(tail>top&&q[top]<=lef[i])
                top++;
            modify(lef[i],1,dp[lef[i]]+a[q[top]]);
            rec=inf;
            if(tail-top>=2)
                query(lef[i],q[tail-2],1);
            else
                query(lef[i],lef[i],1);
            dp[i]=rec;
           //  printf("i %d %I64d\n",i,dp[i]);
        }
        printf("%I64d\n",dp[n]);
    }
}
