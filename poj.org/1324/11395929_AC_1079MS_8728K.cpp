#include <iostream>
#include <queue>
using namespace std;

char pMatrix[21][21][16384];//2^14=16384
char stone[21][21];
int n,m,L,K;
int maxstep,minstep;
struct _Point
{
    int x,y;
};

_Point pt[8];

void setmap(_Point* _pt)
{
    for (int i=1;i<L;i++)//去头
        stone[_pt[i].x][_pt[i].y]=1;
}

void clearmap(_Point* _pt)
{
    for (int i=1;i<L;i++)//去头
        stone[_pt[i].x][_pt[i].y]=0;
}

int bfs(char stone1[][21])
{
    queue<int> Q;
    Q.push(1);Q.push(1);Q.push(0);
    while (!Q.empty())
    {
        int x=Q.front();Q.pop();
        int y=Q.front();Q.pop();
        int _count=Q.front();Q.pop();
        int curx,cury;
        for (int i=0;i<4;i++)
        {
            curx=x,cury=y;
            if (i==0) curx--;
            else if (i==1) curx++;
            else if (i==2) cury--;
            else if (i==3) cury++;
            if (curx<1||curx>n||cury<1||cury>m||stone1[curx][cury]) continue;
            stone1[curx][cury]=1;
            if (curx==pt[0].x&&cury==pt[0].y)
                return _count+1;
            Q.push(curx);Q.push(cury);Q.push(_count+1);
        }
    }
    return -1;
}

bool getmaxmin()
{
    maxstep=0,minstep=0;
    char stone1[21][21];
    memcpy(stone1,stone,sizeof(stone));
    minstep=bfs(stone1);
    if (minstep==-1)
        return false;
    memcpy(stone1,stone,sizeof(stone));
    setmap(pt);
    maxstep=bfs(stone);
    if (maxstep==-1)
        maxstep=0xffff;
    memcpy(stone,stone1,sizeof(stone));
    return true;
}

int getstate()
{
    int tmp=0,i;
    for (i=1;i<L;i++)
    {
        tmp<<=2;
        if (pt[i].x>pt[i-1].x) tmp|=0;
        else if (pt[i].x<pt[i-1].x) tmp|=1;
        else if (pt[i].y>pt[i-1].y) tmp|=2;
        else tmp|=3;
    }
    return tmp;
}

void getcoord(int state,int x,int y)
{
    pt[0].x=x;pt[0].y=y;
    int mask=3;
    for (int i=1;i<L;i++)
    {
        pt[i].x=pt[i-1].x;pt[i].y=pt[i-1].y;
        int tmp=(state>>((L-i-1)*2))&mask;
        if (tmp==0) pt[i].x++;
        else if(tmp==1) pt[i].x--;
        else if(tmp==2) pt[i].y++;
        else pt[i].y--;
    }
}

inline bool check(int x,int y,int state)
{
    return !(x<1||x>n||y<1||y>m||stone[x][y]||pMatrix[x][y][state]);
}

int bfs()
{
    queue<int> Q;
    int state=getstate();
    Q.push(pt[0].x);Q.push(pt[0].y);Q.push(state);Q.push(0);
    while (!Q.empty())
    {
        int x=Q.front();Q.pop();
        int y=Q.front();Q.pop();
        state=Q.front();Q.pop();
        int _count=Q.front();Q.pop();
        getcoord(state,x,y);
        setmap(pt);
        int curx,cury,curstate;
        for (int i=0;i<4;i++)
        {
            curx=x,cury=y;
            if (i==0) curx--;
            else if (i==1) curx++;
            else if (i==2) cury--;
            else if (i==3) cury++;
            if (_count+curx+cury-1>maxstep)
                continue;
            curstate=(L<2)?0:(state>>2)|(i<<((L-2)*2));
            if (!check(curx,cury,curstate)) continue;
            pMatrix[curx][cury][curstate]=1;
            if (curx==1&&cury==1)
                return _count+1;
            Q.push(curx);Q.push(cury);Q.push(curstate);Q.push(_count+1);
        }
        clearmap(pt);
    }
    return -1;
}

int main()
{
    int i,j=0;
    while (scanf("%d%d%d",&n,&m,&L),n&&m&&L)
    {
        j++;
        for (i=0;i<L;i++)
            scanf("%d%d",&pt[i].x,&pt[i].y);
        int x,y;
        scanf("%d",&K);
        memset(stone,0,sizeof(stone));
        memset(pMatrix,0,sizeof(pMatrix));
        for (i=0;i<K;i++)
        {
            scanf("%d%d",&x,&y);
            stone[x][y]=1;
        }
        
        if (pt[0].x==1&&pt[0].y==1) 
            printf("Case %d: %d\n",j,0);
        else if (!getmaxmin())
            printf("Case %d: %d\n",j,-1);
        else if (maxstep==minstep)
            printf("Case %d: %d\n",j,maxstep);
        else
            printf("Case %d: %d\n",j,bfs());
    }
    return 0;
}