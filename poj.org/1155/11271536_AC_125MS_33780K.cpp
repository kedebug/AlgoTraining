#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define INF (1<<30)
const int N=3005;
struct Edge
{
	int v,w;
	Edge* nxt;
}memo[N*N],*cur,*adj[N];

int dp[N][N],n,m;
int num[N];

void addEdge(int u,int v,int w)
{
	cur->v=v; cur->w=w;
	cur->nxt=adj[u];
	adj[u]=cur++;
}
void dfs(int u,int fa)
{
	for(Edge* it=adj[u];it;it=it->nxt)
	{
		int v=it->v,w=it->w;
		if(v==fa) continue;
		dfs(v,u);
		num[u]+=num[v];
		for(int i=num[u];i>=1;i--)
			for(int j=1;j<=i;j++)
				if(dp[u][i-j]!=-INF&&dp[v][j]!=-INF) 
					dp[u][i]=max(dp[u][i],dp[u][i-j]+dp[v][j]-w);
	}
}
void init()
{
	cur=memo;
	memset(adj,0,sizeof(adj));
	memset(num,0,sizeof(num));
	for(int i=0;i<=n;i++)
	{
		dp[i][0]=0;
		for(int j=1;j<=m;j++) dp[i][j]=-INF;
	}
}
int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		init();

		int v,w,k;
		for(int i=1;i<=n-m;i++)
		{
			scanf("%d",&k);
			for(int j=0;j<k;j++)
			{
				scanf("%d%d",&v,&w);
				addEdge(i,v,w);
				addEdge(v,i,w);
			}
		}
		for(int i=n-m+1;i<=n;i++) 
			scanf("%d",&dp[i][1]),num[i]=1;

		dfs(1,-1);
		for(int i=m;i>=0;i--)
		{
			if(dp[1][i]>=0)
			{
				printf("%d\n",i);
				break;
			}
		}
	}
	return 0;
}