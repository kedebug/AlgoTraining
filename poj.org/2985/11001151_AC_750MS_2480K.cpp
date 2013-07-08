#include <iostream>
using namespace std;
const int N=200010;
int c[N],p[N],s[N],n,m;
int find(int x)
{
    if(x==p[x])
        return x;
    return p[x]=find(p[x]);
}
void add(int x,int d)
{
    for(int i=x;i<=n;i+=i&-i)
        c[i]+=d;
}
int sum(int x)
{
    int ans=0;
    for(int i=x;i>0;i-=i&-i)
        ans+=c[i];
    return ans;
}
int main()
{
    int i,sty,x,y;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
        c[i]=0,p[i]=i,s[i]=1;
    add(1,n);
    int num=n;
    for(i=1;i<=m;i++)
    {
        scanf("%d",&sty);
        if(sty==0)
        {
            scanf("%d%d",&x,&y);
            int px=find(x),py=find(y);
            if(px==py)
                continue;
            add(s[px],-1);
            add(s[py],-1);
            add(s[py]=s[py]+s[px],1);
            p[px]=py;
            num--;
        }
        else
        {
            scanf("%d",&x);
            x=num-x+1;
            int l=1,r=n;
            while(l<=r)
            {
                int mid=(l+r)/2;
                if(x<=sum(mid))
                    r=mid-1;
                else
                    l=mid+1;
            }
            printf("%d\n",l);
        }
    }
    return 0;
}