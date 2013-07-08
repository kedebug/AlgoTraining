#include "stdio.h"
#include "string.h"
#include <algorithm>
using namespace std;
#define M 15
#define N 25

int n,k,l,w,ans;
char s[N][M];
char s1[M],s2[M];
int a[N][N],b[N][N],f[N],pre[N];
bool v[N];

struct line
{
    int p1,p2,w;
}all[1010];

int cmp(line a,line b)
{
    return a.w<b.w;
}

int search(char *x)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(strcmp(s[i],x)==0)
            return i;
    }
    return -1;
}

int root(int x)
{
    if(f[x]==x)
        return x;
    f[x]=root(f[x]);
    return f[x];
}

void kruscal()
{
    int i,k1,k2;
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    sort(all,all+l,cmp);
    for(i=0;i<n;i++)
        f[i]=i;
    for(i=0;i<l;i++)
    {
        k1=root(all[i].p1);
        k2=root(all[i].p2);
        if(k1==0||k2==0)
            continue;
        if(k1==k2)
            continue;
        f[k1]=k2;
        k1=all[i].p1;
        k2=all[i].p2;
        a[k1][k2]=all[i].w;
        a[k2][k1]=all[i].w;
        b[k1][k2]=a[k1][k2];
        b[k2][k1]=a[k1][k2];
        ans+=a[k1][k2];
    }
}

void dfs(int x)
{
    int i;
    if(x==0)
    {
        return ;
    }
    v[x]=1;
    for(i=0;i<n;i++)
    {
        if(v[i])
            continue;
        if(b[x][i]==0)
            continue;
        pre[i]=x;
        dfs(i);
    }
}
int main()
{
    int i,j;
    int p1,p2;
    strcpy(s[0],"Park");
    while(scanf("%d",&l)>0)
    {
        n=1;ans=0;
        for(i=0;i<l;i++)
        {
            scanf("%s%s%d",s1,s2,&w);
            p1=search(s1);
            if(p1==-1)
            {
                strcpy(s[n],s1);
                p1=n;
                n++;
            }
            p2=search(s2);
            if(p2==-1)
            {
                strcpy(s[n],s2);
                p2=n;
                n++;
            }
            all[i].p1=p1;
            all[i].p2=p2;
            all[i].w=w;
        }
        scanf("%d",&k);
        kruscal();
        for(i=0;i<l;i++)
        {
            if(all[i].p1!=0&&all[i].p2!=0)
                continue;
            a[all[i].p1][all[i].p2]=all[i].w;
            a[all[i].p2][all[i].p1]=all[i].w;
        }
        memset(v,0,sizeof(v));
        for(i=0;i<n;i++)
        {
            int min,p=-1;
            if(v[i])
                continue;
            if(a[0][i]==0)
                continue;
            for(j=i;j<n;j++)
            {
                if(a[0][j]==0)
                    continue;
                if(root(j)==root(i))
                {
                    v[j]=1;
                    if(p==-1||a[0][j]<min)
                    {
                        min=a[0][j];
                        p=j;
                    }
                }
            }
            b[0][p]=a[0][p];
            b[p][0]=a[0][p];
            ans+=a[0][p];
            k--;
        }
        while(k)
        {
            p1=-1;p2=0;
            int px,mindis;
            line min;
            for(i=1;i<n;i++)
            {
                if(b[0][i])
                    continue;
                if(a[0][i]==0)
                    continue;
                memset(v,0,sizeof(v));
                memset(pre,-1,sizeof(pre));
                dfs(i);
                for(px=-1,j=pre[0];j!=i;j=pre[j])
                {
                    if(px==-1||a[pre[j]][j]>mindis)
                    {
                        px=j;
                        mindis=a[pre[j]][j];
                    }
                }
                if(mindis>p2+a[0][i])
                {
                    p2=mindis-a[0][i];
                    p1=i;
                    min.w=mindis;
                    min.p1=px;
                    min.p2=pre[px];
                }
            }
            if(p1==-1)
                break;
            k--;
            b[0][p1]=a[0][p1];
            b[p1][0]=a[0][p1];
            b[min.p1][min.p2]=0;
            b[min.p2][min.p1]=0;
            ans-=p2;
        }
        printf("Total miles driven: %d\n",ans);
    }
    return 0;
}