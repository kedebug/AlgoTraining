#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int MAXN = 1010;
const int MAXM = 5010;
const double INF = 1000000000;
struct node{
       int va,t;
};
vector<node> vec[MAXN];
deque<int> que;
int f[MAXN],n;
int vis[MAXN],num[MAXN];
int spfa(double mid) {
       int u,i,va;
       double dis[MAXN];
       que.clear();
       for(i=0;i<=n;i++) { dis[i] = INF , vis[i] = 0 , num[i] = 0; }
       dis[1] = 0 , vis[1] = 1;
       que.push_back(1) , num[1]++;
       while(!que.empty()) {
              int x = que.front(); que.pop_front(); vis[x] = 0; // 记住
              int len = vec[x].size();
              for(i=0;i<len;i++) {
                     u = vec[x][i].t , va = vec[x][i].va;
                     if(dis[u]>dis[x]+mid*va-f[x]) {
                            dis[u] = dis[x] + mid*va - f[x];
                            if(!vis[u]) {
                                   vis[u] = 1;
                                   if(++num[u]>n) return 0;
                                   que.push_back(u);
                            }
                     }
              }
       }
       return 1;
}
int main()
{
       int m,i,j,a,b,v;
       while(scanf("%d %d",&n,&m)!=EOF) {
              for(i=1;i<=n;i++) {
                     scanf("%d",&f[i]);
                     vec[i].clear();
              }
              node tmp;
              for(i=1;i<=m;i++) {
                     scanf("%d %d %d",&a,&b,&v);
                     tmp.t = b , tmp.va = v;
                     vec[a].push_back(tmp);
              }
              int l = 0 , r = 10000000 , mid , res;
              while(l<=r) {
                     mid = (l+r)/2;
                     if(spfa(mid*1.0/1000)) r = mid - 1 ;
                     else l = mid + 1,res = mid;
              }
              if(res%10>4) res = (res/10+1)*10;
              else res = (res/10)*10;
              printf("%.2lf\n",res*1.0/1000);
       }
       return 0;
}