#include<cstdio>
#include<algorithm>
using namespace std;
const int mm=444;
struct block
{
    int h,a,c;
}g[mm];
bool f[44444];
int i,j,k,n;
bool cmp(block a,block b)
{
    return a.a<b.a;
}
int main()
{
    while(scanf("%d",&n)!=-1)
    {
        for(i=0;i<n;++i)scanf("%d%d%d",&g[i].h,&g[i].a,&g[i].c);
        sort(g,g+n,cmp);
        for(f[0]=1,i=g[n-1].a;i>0;--i)f[i]=0;
        for(i=0;i<n;++i)
            for(j=0;j<g[i].c;++j)
                for(k=g[i].a;k>=g[i].h;--k)
                    f[k]|=f[k-g[i].h];
        for(i=g[n-1].a;i>0;--i)
            if(f[i])break;
        printf("%d\n",i);
    }
    return 0;
}
