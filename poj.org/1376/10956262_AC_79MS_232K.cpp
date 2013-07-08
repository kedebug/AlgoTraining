#include <cstdlib>  
#include <stdio.h>  
#include <string.h>  
#include <queue>  
#define N 55  
#define MAX 0x7fffffff  
using namespace std;  
/* 
 *  
 */  
struct node  
{  
    int x,y,step,way;  
}s,e;  
int r,c,map[N][N],d[4][2]={0,1,1,0,0,-1,-1,0};  
int used[N][N][4];  
char str[10];  
bool ok(int x,int y,node cur)  
{  
    return x>0&&x<r&&y>0&&y<c&&used[x][y][cur.way]>cur.step+1;  
}  
int bfs()  
{  
    int i;  
    queue<node> q;  
    while(!q.empty())  
        q.pop();  
    q.push(s);  
    node cur,next;  
    while(!q.empty())  
    {  
        cur=q.front();  
        q.pop();  
        if(cur.x==e.x&&cur.y==e.y)  
            return cur.step;  
        if(cur.step+1<used[cur.x][cur.y][(cur.way+1)%4])  
        {  
            next=cur;  
            next.step++;  
            next.way=(cur.way+1)%4;  
            q.push(next);  
            used[cur.x][cur.y][(cur.way+1)%4]=cur.step+1;  
        }  
        if(cur.step+1<used[cur.x][cur.y][(cur.way+4-1)%4])  
        {  
            next=cur;  
            next.step++;  
            next.way=(cur.way+4-1)%4;  
            q.push(next);  
            used[cur.x][cur.y][(cur.way+4-1)%4]=cur.step+1;  
        }  
        for(i=1;i<=3;i++)  
        {  
            int tx,ty;  
            tx=cur.x+i*d[cur.way][0];  
            ty=cur.y+i*d[cur.way][1];  
            if(map[tx][ty]==1)  
                break;  
            if(ok(tx,ty,cur))  
            {  
                next.x=tx;  
                next.y=ty;  
                next.step=cur.step+1;  
                next.way=cur.way;  
                q.push(next);  
                used[tx][ty][cur.way]=next.step;  
            }  
        }  
    }  
    return -1;  
}  
int main(int argc, char** argv)  
{  
    int i,j;  
    while(scanf("%d%d",&r,&c)&&(r||c))  
    {  
        memset(map,0,sizeof(map));  
        for(i=0;i<r;i++)  
            for(j=0;j<c;j++)  
            {  
                int temp;  
                scanf("%d",&temp);  
                if(temp==1)                
                    map[i][j]=map[i+1][j]=map[i][j+1]=map[i+1][j+1]=1;                  
                used[i][j][0]=used[i][j][1]=used[i][j][2]=used[i][j][3]=MAX;  
            }  
        scanf("%d%d%d%d%s",&s.x,&s.y,&e.x,&e.y,str);  
        if(!strcmp(str,"east"))  
            s.way=0;  
        if(!strcmp(str,"south"))  
            s.way=1;  
        if(!strcmp(str,"west"))  
            s.way=2;  
        if(!strcmp(str,"north"))  
            s.way=3;  
        s.step=0;  
        printf("%d\n",bfs());  
    }  
    return 0;  
}  