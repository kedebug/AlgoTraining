#include<cstdio>
 #include<cstring>
 #include<cmath>
 #include<iostream>
 #include<algorithm>
 #include<set>
 #include<map>
 #include<queue>
 #include<vector>
 #include<string>
 #define Min(a,b) a<b?a:b
 #define Max(a,b) a>b?a:b
 #define CL(a,num) memset(a,num,sizeof(a));
 #define eps  1e-12
 #define inf   0x7fffffff
 
 //freopen("data.txt","r",stdin);
 const double pi  = acos(-1.0);
 typedef   __int64  ll;
 const int maxn = 1200 ;
 using namespace std;
 struct node
 {
 
     int v;
     int len ;
     int next ;
 }p[maxn*10*2] ;
 struct qnode
 {
     int d;
     int  u ;
     int cost ;
     qnode(int x,int y,int z):u(x),d(y),cost(z){}
     friend bool operator < (qnode a,qnode b)
     {
         return  a.cost > b.cost ;
     }
 };
 int num,a[maxn],next[maxn],dp[maxn][102],n,m,vis[maxn][102];
 void add(int u ,int  v,int len)
 {
     p[num].v = v;
     p[num].len = len ;
     p[num].next = next[u] ;
     next[u] = num++;
 }
 priority_queue<qnode>que;
 int bfs(int s,int e,int c)
 {
 
     int i , j ;
     while(!que.empty())que.pop();
 
     for(i = 0 ; i <= n;i++ )
     {
         for(j = 0; j<= c;j++)
            dp[i][j] = inf ;
     }
     
    CL(vis,0);
    
    dp[s][0] = 0 ;
    
    que.push(qnode(s,0,0));
 
    while(!que.empty())
    {
        qnode  b = que.top();que.pop();
 
        int u = b.u;
        int cost = b.cost;
        int d = b.d ;
         vis[u][d] = 1;// 标记  已经找到了 的 最小的  ，下面就不用 再扩展的 此节点了
         if(u == e) return  cost ;// 用的是 优先队列 所以 出来的定是 最小的 ；
 
        if(d+1 <= c &&!vis[u][d + 1] && dp[u][d+1]> dp[u][d] + a[u])//油量 加 1
        {
            dp[u][d + 1] = dp[u][d] + a[u] ;
            que.push(qnode(u,d+1,dp[u][d+1]));
 
        }
        for(i = next[u];i!= -1;i = p[i].next)// 直接 走向 相邻 节点 ；
        {
            int v = p[i].v ;
            int len = p[i].len ;
 
            if(d >= len &&!vis[v][d - len] && dp[v][d - len] > cost)
            {
                dp[v][d - len] = cost ;
                que.push(qnode(v,d - len,cost));
            }
 
 
        }
 
 
    }
 
 
     return -1 ;
 }
 int main()
 {
     //freopen("data.txt","r",stdin);
      int s,e,c,i,x,y,d,q;
      while(~scanf("%d%d",&n,&m))
      {
          for(i = 0;i < n;i++)  scanf("%d",&a[i]) ;
 
         CL(next,-1) ;
         num = 0 ;
         for(i = 0 ;i< m;i++)
        {
          scanf("%d%d%d",&x,&y,&d);
          add(x,y,d);
          add(y,x,d);
        }
 
        scanf("%d",&q);
 
         while(q--)
         {
            scanf("%d%d%d",&c,&s,&e);
             int ans = bfs(s,e,c);
             if(ans != -1)printf("%d\n",ans);
             else puts("impossible");
         }
      }
 
 }