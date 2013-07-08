#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int T,n,m;
int head[1010],to[6010],next[6010],graphmr;
int head1[1010],to1[6010],next1[6010],graphmr1;
int dfn[1010],low[1010],idx,stack[1010],top;
bool instack[1010];
int belong[1010],scc;
int indeg[1010],q[1010],h,t;
inline void add(int x,int y)
{
    int p=graphmr++;
    to[p]=y;
    next[p]=head[x];
    head[x]=p;
}
inline void add1(int x,int y)
{
    int p=graphmr1++;
    to1[p]=y;
    next1[p]=head1[x];
    head1[x]=p;
}
inline void tarjan(int x)
{
    dfn[x]=low[x]=++idx;
    stack[++top]=x;
    instack[x]=1;
    for(int i=head[x];~i;i=next[i])
        if(!dfn[to[i]])
        {
            tarjan(to[i]);
            low[x]=min(low[x],low[to[i]]);
        }
        else if(instack[to[i]])
            low[x]=min(low[x],dfn[to[i]]);
    if(dfn[x]==low[x])
    {
        scc++;
        int v;
        do
        {
            v=stack[top--];
            instack[v]=0;
            belong[v]=scc;
        }while(v!=x);
    }
}
inline bool topsort()
{
    h=1;t=0;
    for(int i=1;i<=scc;i++)
        if(!indeg[i])
        {
            q[++t]=i;
            if(t==2) return false;
        }
        while(h<=t)
        {
            int sta=q[h++];
            bool flag=false;
            for(int i=head1[sta];~i;i=next1[i])
            {
                indeg[to1[i]]--;
                if(indeg[to1[i]]==0)
                {
                    q[++t]=to1[i];
                    if(flag) return false;
                    flag=true;
                }
            }
        }
        return true;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        memset(head,-1,sizeof head);
        memset(head1,-1,sizeof head1);
        graphmr=0;
        graphmr1=0;
        scanf("%d%d",&n,&m);
        for(int i=1,x,y;i<=m;i++)
        {
            scanf("%d%d",&x,&y);
            add(x,y);
        }
        memset(dfn,0,sizeof dfn);
        scc=0;
        for(int i=1;i<=n;i++)
            if(!dfn[i])
                tarjan(i);
        memset(indeg,0,sizeof indeg);
        for(int i=1;i<=n;i++)
            for(int j=head[i];~j;j=next[j])
                if(belong[i]!=belong[to[j]])
                {
                    add1(belong[i],belong[to[j]]);
                    indeg[belong[to[j]]]++;
                }
                if(topsort()) printf("Yes\n");
                else printf("No\n");
    }
    return 0;
}