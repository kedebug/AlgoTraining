#include <stdio.h>
#include <string.h>
#define MAX 110000
#define min(a,b) (a)<(b)?(a):(b)
#define Rabs(a)  (a<0?-a:a)
#define int64 __int64
#define INF 21474836470000000


struct node {

	int v;
	node *next;
}*head[MAX],tree[MAX*2];
int n,m,ptr,val[MAX],vis[MAX];
int64 dp[MAX],ans,cnt,sum;


void Initial() {

	ans = INF;
	sum = ptr = 0;
	memset(vis,0,sizeof(vis));
	memset(head,NULL,sizeof(head));
}
void AddEdge(int x,int y) {

	tree[ptr].v = y;
	tree[ptr].next = head[x],head[x] = &tree[ptr++];
	tree[ptr].v = x;
	tree[ptr].next = head[y],head[y] = &tree[ptr++];
}
void Dfs_Ini(int s,int pa) {
	//自底向上计算每个节点的子孙个数
	dp[s] = val[s];
	vis[s] = 1;
	node *p = head[s];


	while (p != NULL) {

		if (vis[p->v] == 0) {

			Dfs_Ini(p->v,s);
			dp[s] += dp[p->v];
		}
		p = p->next;
	}
}
void Dfs_Solve() {

	for (int i = 1; i <= n; ++i) {
		//枚举每一条边
		node *p = head[i];
		while (p != NULL) {
			
			int64 tp = dp[p->v];
			ans = min(ans,Rabs((2 * tp - sum)));
			p = p->next;
		}
	}
}


int main()
{
	int i,j,k,a,b,cas = 0;



	while (scanf("%d%d",&n,&m),n+m) {
	
		Initial();
		for (i = 1; i <= n; ++i)
			scanf("%d",&val[i]),sum += val[i];
		for (i = 1; i <= m; ++i) {

			scanf("%d%d",&a,&b);
			AddEdge(a,b);
		}


		Dfs_Ini(1,0);			//第一次深搜，记录当前节点的子孙总数
		memset(vis,0,sizeof(vis));
		Dfs_Solve();			//更新答案
		printf("Case %d: %I64d\n",++cas,ans);
	}
}
