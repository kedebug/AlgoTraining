#include<stdio.h>
#include<string.h>
#include<algorithm>
#define clr(x)memset(x,0,sizeof(x))
using namespace std;
#define maxn 10010
int f[maxn];
struct node
{
    int w,end;
}q[maxn];
bool operator < (const node& a,const node& b)
{
    return a.w>b.w;
}
int find(int x)
{
    return f[x]==x?x:(f[x]=find(f[x]));
}
int main()
{
    int n,r,res,i;
    while(scanf("%d",&n)!=EOF)
    {
        res=0;
        for(i=0;i<maxn;i++)
            f[i]=i;
        for(i=0;i<n;i++)
            scanf("%d%d",&q[i].w,&q[i].end);
        sort(q,q+n);
        for(i=0;i<n;i++)
        {
            r=find(q[i].end);
            if(r>0)
            {
                f[r]=r-1;
                res+=q[i].w;
            }
        }
        printf("%d\n",res);
    }
    return 0;
}