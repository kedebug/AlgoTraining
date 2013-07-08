#include <stdio.h>
#include <string.h>
#define MAX 3010
#define INF 0xfffffff
#define max(a,b) (a)>(b)?(a):(b)


struct node {

    int v,len;
    node *next;
}*head[MAX*3],tree[MAX*3];
int ans,sum[MAX],vis[MAX];
int n,m,ptr,dp[MAX][MAX],money[MAX];


void AddEdge(int x,int y,int len) {

    tree[ptr].v = y,tree[ptr].len = len;
    tree[ptr].next = head[x],head[x] = &tree[ptr++];
    tree[ptr].v = x,tree[ptr].len = len;
    tree[ptr].next = head[y],head[y] = &tree[ptr++];
}
void Dfs(int v,int len) {

    if (vis[v]) return ;
    vis[v] = 1,dp[v][0] = 0;


    int i,j,k,tot = 0;
    node *p = head[v];


    while (p != NULL) {

        if (!vis[p->v]) {

            tot++;
            Dfs(p->v,len);
            sum[v] += sum[p->v];
        }
        p = p->next;
    }


    if (tot == 0) {
    //根节点
        sum[v] = 1;
        dp[v][1] = money[v] - len;
    }
    else {

        p = head[v];
        while (p != NULL) {

            k = p->v;
            len = p->len;
            for (j = sum[v]; j >= 1; --j)
                for (i = 1; i <= sum[k]; ++i)
                    if (j >= i && dp[v][j-i] != -INF && dp[k][i] != -INF)
                        dp[v][j] = max(dp[v][j],dp[v][j-i] + dp[k][i] - len);
            p = p->next;
        }
    }
}


int main()
{
    int i,j,k,a,b;
    

    while (scanf("%d%d",&n,&m) != EOF) {

        ptr = 1,ans = -INF;
        memset(sum,0,sizeof(sum));
        memset(vis,0,sizeof(vis));
        memset(head,NULL,sizeof(head));
        for (i = 0; i <= n; ++i)
            for (j = 0; j <= n; ++j)
                dp[i][j] = -INF;


        for (i = 1; i <= n - m; ++i) {

            scanf("%d",&k);
            for (j = 1; j <= k; ++j)
                scanf("%d%d",&a,&b),AddEdge(i,a,b);
        }
        for (i = n - m + 1; i <= n; ++i)
            scanf("%d",&money[i]);


        Dfs(1,0);
        for (i = n; i >= 0; --i)
            if (dp[1][i] >= 0) {
                
                printf("%d\n",i);
                break;
            }
        
    }
    return 0;
}