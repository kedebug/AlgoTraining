#include<iostream>
using namespace std;
#define MAX 502
#define LINEMAX 9000000

struct node
{
    int x,y;
    int step;
    int state;//1代表直立，2代表水平放，3代表垂直放
};

bool visit[MAX][MAX][4];
int graph[MAX][MAX];//0->empty cell，1->weak cell,2->rigid cell
node l[LINEMAX];

int dir[3][4][3]={{{0,-1,2},{-2,0,1},{0,2,2},{1,0,1}},
                {{0,-1,0},{-1,0,-1},{0,1,0},{2,0,-1}},
                {{0,-2,-2},{-1,0,0},{0,1,-2},{1,0,0}}};




inline bool check(int x,int y,int state)
{
    if(graph[x][y]==0) return false;
    if(state==1&&graph[x][y]==1) return false;
    else if(state==2&&graph[x+1][y]==0)    return false;
    else if(state==3&&graph[x][y-1]==0)    return false;
    return true;
}



inline node inputgraph(int r,int c,int &endx,int &endy)
{

    int i,j;
    int len;
    char temp[MAX];
    int x1=0,y1=0;
    int x2=0,y2=0;
    int flag=0;
    node s;    
    memset(graph,0,sizeof(graph));//Graph矩阵清0
    memset(visit,0,sizeof(visit));//visit矩阵清0
    for(i=1;i<=r;i++)
    {

        scanf("%s",temp);
        len=strlen(temp);
        for(j=0;j<len;j++)
        {
            if(temp[j]=='#') graph[j+1][i]=0;
            else if(temp[j]=='E') graph[j+1][i]=1;
            else if(temp[j]=='.') graph[j+1][i]=2;
            else if(temp[j]=='X'&&flag==0)
            {
                graph[j+1][i]=2;
                x1=j+1;y1=i;
                flag=1;
            }
            else if(temp[j]=='X'&&flag==1)
            {
                graph[j+1][i]=2;
                x2=j+1;y2=i;
            }
            else if(temp[j]=='O')
            {

                graph[j+1][i]=2;
                endx=j+1;
                endy=i;
            }
        }
    }
    if(x1!=0&&x2!=0&&y1!=0&&y2!=0)
    {
        if(y1<y2) {s.x=x1;s.y=y2;s.state=3;}
        else if(x1<x2) {s.x=x1;s.y=y1;s.state=2;}
    }
    else {s.x=x1;s.y=y1;s.state=1;}
    s.step=0;
    return s;
}


int main()
{
    
    int r,c;
    int i,j;
    int endx,endy;
    int newx,newy;
    int newstate;
    while(scanf("%d%d",&r,&c))
    {
        
        if(r==0&&c==0)
            break;
        int front=1;
        int rear=1;
        l[front]=inputgraph(r,c,endx,endy);
        visit[l[front].x][l[front].y][l[front].state]=1;
        while(front<=rear)
        {
            if(l[front].x==endx&&l[front].y==endy&&l[front].state==1)
            {
                printf("%d\n",l[front].step);
                break;
            }

            for(j=0;j<4;j++)
            {
                newx=l[front].x+dir[l[front].state-1][j][0];
                newy=l[front].y+dir[l[front].state-1][j][1];
                newstate=l[front].state+dir[l[front].state-1][j][2];
                if(!visit[newx][newy][newstate]&&check(newx,newy,newstate))
                {
                    
                    rear=rear++;
                    l[rear].x=newx;
                    l[rear].y=newy;
                    l[rear].state=newstate;
                    visit[newx][newy][newstate]=1;
                    l[rear].step=l[front].step+1;
                }
            }
        
        front++;
        }
        if(front>rear)
            printf("Impossible\n");
    }
    return 0;
}