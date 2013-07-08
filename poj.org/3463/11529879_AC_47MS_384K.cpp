#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int MAXN=1010;
const int INF=1000000000;

bool vi[MAXN][2];
int dist[MAXN][2],cnt[MAXN][2];//0 表示最短路 1表示次短路
int G[MAXN];
int n,m,alloc;

struct Node{
    int v,w,next;
}nodes[MAXN*10];

struct Pos{
    int v,flag;
    Pos(int vv,int f){v=vv,flag=f;}
    bool operator<(const Pos &p)const {
        return dist[v][flag]>dist[p.v][p.flag];
    }
};

void add(int a,int b,int c){
    alloc++;
    nodes[alloc].v=b,nodes[alloc].w=c,nodes[alloc].next=G[a];
    G[a]=alloc;
}

int dij(int s,int t){
    memset(vi,0,sizeof(vi));
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=n;i++)
        dist[i][0]=dist[i][1]=INF;
    priority_queue<Pos>Q;
    Q.push(Pos(s,0));
    dist[s][0]=0;cnt[s][0]=1;
    while(!Q.empty()){
        Pos top=Q.top();Q.pop();
        int u=top.v,flag=top.flag;
        if(vi[u][flag])continue;
        vi[u][flag]=1;
        for(int son=G[u];son;son=nodes[son].next){
            int v=nodes[son].v,w=dist[u][flag]+nodes[son].w;
            if(w<dist[v][0]){
                if(dist[v][0]!=INF){
                    dist[v][1]=dist[v][0];
                    cnt[v][1]=cnt[v][0];
                    Q.push(Pos(v,1));
                }
                dist[v][0]=w;
                cnt[v][0]=cnt[u][flag];
                Q.push(Pos(v,0));
            }
            else if(w==dist[v][0])cnt[v][0]+=cnt[u][flag];
            else if(w<dist[v][1]){
                dist[v][1]=w;
                cnt[v][1]=cnt[u][flag];
                Q.push(Pos(v,1));
            }
            else if(w==dist[v][1])cnt[v][1]+=cnt[u][flag];
        }
    }

    int ans=cnt[t][0];
    if(dist[t][0]==dist[t][1]-1)ans+=cnt[t][1];
    return ans;
}
int main(){
    int T,a,b,c;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        memset(G,0,sizeof(G));
        alloc=0;
        while(m--){
            scanf("%d%d%d",&a,&b,&c);
            add(a,b,c);
        }
        scanf("%d%d",&a,&b);
        printf("%d\n",dij(a,b));
    }
    return 0;
}