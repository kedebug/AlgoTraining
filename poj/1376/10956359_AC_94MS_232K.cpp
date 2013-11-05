//
// http://blog.csdn.net/euler_m/article/details/6131920
//
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 55;
const int INF = 0x7FFFFFFF;
int m, n;
int mat[MAXN][MAXN];
int used[MAXN][MAXN][4];
int dir[4][2] = { 0,1,1,0,0,-1,-1,0 }; 

typedef struct _Node {
    int x, y;
    int step, way;
} Node;

Node s, e;

int bfs()
{
    Node a, b;
    queue<Node> q;

    while (!q.empty())
        q.pop();

    q.push(s);

    while (!q.empty())
    {
        a = q.front();
        q.pop();
        if (a.x == e.x && a.y == e.y)
            return a.step;
        if (a.step + 1 < used[a.x][a.y][(a.way+1)%4])
        {
            b = a;
            b.step++;
            b.way = (a.way+1) % 4;
            q.push(b);
            used[a.x][a.y][(a.way+1)%4] = a.step;
        }
        if (a.step + 1 < used[a.x][a.y][(a.way+4-1)%4])
        {
            b = a;
            b.step++;
            b.way = (a.way+4-1) % 4;
            q.push(b);
            used[a.x][a.y][(a.way+4-1)%4] = a.step;
        }
        int i;
        int tx, ty;
        for (i = 1; i <= 3; ++i)
        {
            tx = a.x + i * dir[a.way][0];
            ty = a.y + i * dir[a.way][1];
            if (mat[tx][ty] == 1)
                break;
            if (0 < tx && tx < m && 0 < ty && ty < n &&
                used[tx][ty][a.way] > a.step + 1)
            {
                b.x = tx;
                b.y = ty;
                b.step = a.step + 1;
                b.way = a.way;
                q.push(b);
                used[tx][ty][a.way] = b.step;
            }
        }
    }
    return -1;
}

int main()
{
    while (scanf("%d %d", &m, &n) && m && n)
    {
        int i, j;
        memset(mat, 0, sizeof(mat));
        for (i = 0; i < m; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                int t;
                scanf("%d", &t);
                if (t == 1)
                    mat[i][j] = mat[i+1][j] = mat[i][j+1] = mat[i+1][j+1] = 1;
                used[i][j][0] = used[i][j][1] = used[i][j][2] = used[i][j][3] = INF;    
            } 
        }
        char str[16];
        scanf("%d %d %d %d %s", &s.x, &s.y, &e.x, &e.y, str);
        if(!strcmp(str, "east"))  
            s.way = 0;  
        if(!strcmp(str, "south"))  
            s.way = 1;  
        if(!strcmp(str, "west"))  
            s.way = 2;  
        if(!strcmp(str, "north"))  
            s.way = 3;  
        s.step = 0;
        printf("%d\n", bfs());
    }
    return 0;
}