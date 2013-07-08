#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>

using namespace std;

#define N 100010

bool visit[N];//判断该点在dfs中是否访问过，非映射
int apple[N];//判断该点是否有苹果，映射
int lowbit[N];
int map[N];//存放映射
int low[N];//存放当前节点子节点的最小编号，非映射
int c[N];//存放区间的苹果数
typedef vector<int> INT;
vector<INT> G(N);
int n;
int time=1;

inline void init(void)
{
    int i;
    for(i=1;i<=N-10;i++)
    {
        c[i]=i&(-i);
        apple[i]=true;
        lowbit[i]=c[i];
    }
    return ;
}

void dfs(int v)
{
    visit[v]=true;
    low[v]=time;//最小子节点编号
    int i;
    for(i=0;i<G[v].size();i++)
    {
        if(!visit[G[v][i]])
            dfs(G[v][i]);
    }
    map[v]=time++;//映射到新点
}

void update(int a)
{
    int t;
    if(apple[a])
    {
        apple[a]=false;
        t=-1;
    }
    else 
    {
        apple[a]=true;
        t=1;
    }
    while(a<=n)
    {
        c[a]+=t;
        a+=lowbit[a];
    }
}

int sum(int a)
{
    int s=0;
    while(a>0)
    {
        s+=c[a];
        a-=lowbit[a];
    }
    return s;
}

int main(void)
{
    init();
    scanf("%d",&n);
    int i;
    for(i=1;i<=n-1;i++)
    {
        int a,b;
        scanf("%d %d",&a,&b);//去看了别人的程序，有的人只加了一条边，这样可以么。。？
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dfs(1);
//    printf("%d\n",time);
    int q;
    scanf("%d",&q);
    char s[3];
    int v;
    for(i=1;i<=q;i++)
    {
        scanf("%s%d",s,&v);
        if(s[0]=='Q')
        {
            printf("%d\n",sum(map[v])-sum(low[v]-1));
        }
        else if(s[0]=='C')
        {
            update(map[v]);
        }
    }
    return 0;
}