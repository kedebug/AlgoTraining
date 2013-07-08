#include<cstdio>
#include<iostream>
using namespace std;
const int mm=1111;
int g[mm],f[mm],w[11];
bool v[111];
int i,j,n,c1,c2,t,s,cas=0;
bool ok(int x)
{
    int i,j,sum=0;
    for(i=0;i<=c1;++i)v[i]=0;
    v[0]=1;
    for(i=0;i<n;++i)
        if(x&(1<<i))
        {
            sum+=w[i];
            for(j=c1-w[i];j>=0;--j)
                if(v[j])v[j+w[i]]=1;
        }
    for(i=c1;i>=0;--i)
        if(v[i]&&sum-i<=c2)return 1;
    return 0;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&c1,&c2);
        if(c1>c2)swap(c1,c2);
        for(i=0;i<n;++i)scanf("%d",&w[i]);
        for(s=0,i=1;i<1<<n;++i)
            if(ok(i))g[s++]=i;
        for(i=0;i<1<<n;++i)f[i]=1000000000;
        f[0]=0;
        for(i=0;i<s;++i)
            for(j=(1<<n)-1-g[i];j>=0;--j)
                if(!(j&g[i]))f[j|g[i]]=min(f[j|g[i]],f[j]+1);
        printf("Scenario #%d:\n%d\n\n",++cas,f[(1<<n)-1]);
    }
    return 0;
}
