#include <cstdio>
int i,j,n,m,ans,v[100],c[100],t[100001];
bool p[100001];
int main()
{
    while(scanf("%d %d", &n, &m),n)
    {
        for(i=0;i<n;++i)scanf("%d",v+i);
        for(i=0;i<n;++i)scanf("%d",c+i);
        for(p[0]=i=1;i<=m;++i)p[i]=0;
        for(ans=i=0; i<n; ++i)
        {
            for(j=0; j<=m;++j)t[j]=0;
            for(j=v[i];j<=m;++j)
                if(!p[j]&&p[j-v[i]]&&t[j-v[i]]<c[i])t[j]=t[j-v[i]]+1,p[j]=1,++ans;
        }
        printf("%d\n",ans);
    }
    return 0;
}