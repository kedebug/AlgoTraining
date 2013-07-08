#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef unsigned char byte;
const int MAXN=22;
const int INF=~0u>>3;
const int dx[]={-1,0,0,1};
const int dy[]={0,-1,1,0};
    
int mindis[MAXN][MAXN];
    
typedef struct node{
   int hx,hy,tx,ty;
   int body,step;
   bool on[MAXN][MAXN];
   bool operator <(const node &t) const{
       return step+mindis[hx][hy]>t.step+mindis[t.hx][t.hy];
   }
}node;
    
    
    
bool stone[MAXN][MAXN];
byte vis[MAXN][MAXN][ 1<<14];
    
node start;
int n,m,l;
int cas=0;
    
inline int
check(int x,int y){
   return x>=1 && x<=n && y>=1 && y<=m && stone[x][y]==false;
}
    
void
getmin(){
   for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) mindis[i][j] = INF;
   mindis[1][1]=0;
   queue<int> q; q.push(1); q.push(1);
   while(!q.empty()) {
       int x=q.front(); q.pop();
       int y=q.front(); q.pop();
       for(int i=0; i<4; i++) {
           int u=x+dx[i]; int v=y+dy[i];
           if(!check(u,v)) continue;
           if(mindis[x][y]+1<mindis[u][v]) {
              mindis[u][v]=mindis[x][y]+1;
              q.push(u); q.push(v);
           }
       }
   }
}
    
void
solve(){
     if(start.hx==1 && start.hy==1) {
         puts("0"); return ;
     }
     priority_queue<node> q; q.push(start);
     node pre,cur;
     while(!q.empty()) {
         pre = q.top(); q.pop();
         for(int i=0; i<4; i++) {
            cur = pre;  int &nx=cur.hx; int &ny=cur.hy;
            nx+=dx[i]; ny+=dy[i];  ++cur.step;
             if(!check(nx,ny)) continue;
             if(cur.on[nx][ny]) continue;
    
             int dir=pre.body&3;
             cur.tx=pre.tx+dx[dir]; cur.ty=pre.ty+dy[dir];
    
             cur.on[ pre.tx ][ pre.ty ]=false;
             cur.on[ cur.hx ][ cur.hy ]=true;
    
             cur.body=cur.body>>2; cur.body|=i<<( l*2-4 );
    
             if(nx==1 && ny==1) {
                 printf("%d\n",cur.step); return ;
             }
    
             if(  vis[nx][ny][cur.body] !=cas) {
                  vis[nx][ny][cur.body] = cas;
                  q.push(cur);
             }
         }
     }
     puts("-1");
}
    
int main(){
    
    while(scanf("%d %d %d",&n,&m,&l)!=EOF) {
         if(n==0 && m==0 && l==0) break;
         memset(stone,false,sizeof(stone));
         memset(start.on,false,sizeof(start.on));
    
             scanf("%d %d",&start.hx,&start.hy);
             int pre_x,pre_y,now_x,now_y;
             now_x=start.hx; now_y=start.hy;
             start.body=0;  start.step=0;
             start.on[start.hx][start.hy]=true;
    
             for(int i=2; i<=l; i++) {
                 pre_x = now_x; pre_y = now_y;
                 scanf("%d%d",&now_x,&now_y);
    
                 for(int j=0; j<4; j++) if(now_x+dx[j]==pre_x && now_y+dy[j]==pre_y) {
                    start.body=start.body*4+j; break;
                 }
                 start.on[now_x][now_y] = true;
             }
             start.tx=now_x; start.ty=now_y;
    
             int stonenum; scanf("%d",&stonenum);
             for(int i=1; i<=stonenum; i++) {
                int x,y; scanf("%d%d",&x,&y); stone[x][y] = true;
             }
    
             vis[start.hx][start.hy][start.body]=cas;
             printf("Case %d: ",++cas);
             getmin();
             solve();
    }
    return 0;
}