#pragma warning (disable:4786)    
#include<iostream>  
#include<vector>  
using namespace std;  
#define INF 0x3F3F3F3F  
int n,m;  
int dist[1002][2];         //最短路与次短路  
int visit[1002][2];        //已访问标记  
int path[1002][2];         //最短路与次短路数目  
struct Edge{              
    int v;  
    int dis;  
};  
vector<Edge> edge[1002];   //邻接表存储  
void dijkstra(int s){  
    int k,i,j,min,flag;  
    path[s][0]=path[s][1]=1;  
    dist[s][0]=0;  
    dist[s][1]=INF;      
    while(1){           //不能用for(i=1;i<=n;i++)  
        min=INF;  
        for(j=1;j<=n;j++){  
            for(i=0;i<2;i++){  
                if(visit[j][i]==0 && dist[j][i]<min){  
                    min=dist[j][i];   
                    k=j;  
                    flag=i;  
                }  
            }  
        }  
        if(min==INF) break;  
        visit[k][flag]=1;  
        for(j=0;j<edge[k].size();j++){  
            Edge e=edge[k][j];  
            if( visit[e.v][0]==0 && dist[e.v][0]>=min+e.dis ){  
                if( dist[e.v][0] > min+e.dis ){  
                    dist[e.v][1]=dist[e.v][0];  
                    path[e.v][1]=path[e.v][0];       //因为此句没加wa了几次  
                    dist[e.v][0]=min+e.dis;  
                    path[e.v][0]=path[k][flag];   
                    continue;  
  
                }  
                else if( dist[e.v][0]==min+e.dis ){  
                        path[e.v][0]+=path[k][flag];  
                }  
            }  
            if( visit[e.v][1]==0 && dist[e.v][1]>=min+e.dis && dist[e.v][0]<min+e.dis ){  
                if( dist[e.v][1]>min+e.dis ){  
                    dist[e.v][1]=min+e.dis;  
                    path[e.v][1]=path[k][flag];  
                }  
                else if( dist[e.v][1]==min+e.dis ){               
                    path[e.v][1]+=path[k][flag];  
                }  
            }  
        }  
    }  
}  
int main(){  
    int t,s,f,a,b,l,i;  
    cin>>t;  
    while(t--){           
        scanf("%d%d",&n,&m);  
        for(i=1;i<=n;i++){  
            edge[i].clear();  
            dist[i][0]=dist[i][1]=INF;  
            path[i][0]=path[i][1]=0;  
            visit[i][0]=visit[i][1]=0;  
        }  
        while(m--){  
            scanf("%d%d%d",&a,&b,&l);  
            Edge e;  
            e.v=b;e.dis=l;  
            edge[a].push_back(e);  
        }  
  
        scanf("%d%d",&s,&f);  
        dijkstra(s);  
        if( dist[f][1]!=dist[f][0]+1 )  
            path[f][1]=0;  
        printf("%d\n",path[f][0]+path[f][1] );  
    }  
}  