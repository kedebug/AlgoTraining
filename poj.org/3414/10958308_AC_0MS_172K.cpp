
//
// http://blog.csdn.net/stormdpzh/article/details/7455640
//
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

typedef struct _Node {
    int x, y;
    int step;
    _Node(int _x, int _y, int _step) : x(_x), y(_y), step(_step) { } 
} Node;

typedef struct _Path {
    int method;
    int pre;
    _Path(int _m, int _p) : method(_m), pre(_p) { }  
} Path;

const int MAXN = 105;
bool vis[MAXN][MAXN];
int a, b, c;
queue<Node> q;
vector<Path> v;

int bfs()
{
    memset(vis, false, sizeof(vis));
    v.clear();
    while (!q.empty())
        q.pop();

    q.push(Node(0, 0, 0));
    vis[0][0] = true;
    v.push_back(Path(-1, -1));

    int idx = -1;
    //Node p;
    int tx, ty;

    while (!q.empty())
    {
        ++idx;
        Node p = q.front();
        q.pop();

        tx = a;
        ty = p.y;
        if (!vis[tx][ty])
        {
            v.push_back(Path(1, idx));
            vis[tx][ty] = true;
            if (tx == c || ty == c)
                return p.step + 1;
            else
                q.push(Node(tx, ty, p.step+1));
        }

        tx = p.x;
        ty = b;
        if (!vis[tx][ty])
        {
            v.push_back(Path(2, idx));
            vis[tx][ty] = true;
            if (tx == c || ty == c)
                return p.step + 1;
            else
                q.push(Node(tx, ty, p.step+1));
        }

        if (p.x + p.y <= b && p.x > 0)
            tx = 0, ty = p.x + p.y;
        else if (p.x > 0)
            tx = p.x + p.y - b, ty = b;

        if (!vis[tx][ty])
        {
            v.push_back(Path(3, idx));
            vis[tx][ty] = true;
            if (tx == c || ty == c)
                return p.step + 1;
            else
                q.push(Node(tx, ty, p.step+1));
        }

        if (p.x + p.y <= a && p.y > 0)
            ty = 0, tx = p.x + p.y;
        else if (p.y > 0)
            ty = p.x + p.y - a, tx = a;

        if (!vis[tx][ty])
        {
            v.push_back(Path(4, idx));
            vis[tx][ty] = true;
            if (tx == c || ty == c)
                return p.step + 1;
            else
                q.push(Node(tx, ty, p.step+1));
        }

        tx = 0;
        ty = p.y;
        if (!vis[tx][ty])
        {
            v.push_back(Path(5, idx));
            vis[tx][ty] = true;
            if (tx == c || ty == c)
                return p.step + 1;
            else
                q.push(Node(tx, ty, p.step+1));
        }

        tx = p.x;
        ty = 0;
        if (!vis[tx][ty])
        {
            v.push_back(Path(6, idx));
            vis[tx][ty] = true;
            if (tx == c || ty == c)
                return p.step + 1;
            else
                q.push(Node(tx, ty, p.step+1));
        }
    }
    return -1;
}

int main()
{
    while (scanf("%d %d %d", &a, &b, &c) != EOF)
    {
        int ans = bfs();
        if (ans == -1)
        {
            printf("impossible\n");
            continue;
        }
        printf("%d\n", ans);

        vector<int> p;
        int i;
        i = v.size() - 1;

        while (v[i].pre != -1)
            p.push_back(v[i].method), i = v[i].pre;

        for (i = p.size() - 1; i >= 0; --i)
        {
            switch (p[i])
            {
            case 1: printf("FILL(1)\n");  
                break;  
            case 2: printf("FILL(2)\n");  
                break;  
            case 3: printf("POUR(1,2)\n");  
                break;  
            case 4: printf("POUR(2,1)\n");  
                break;  
            case 5: printf("DROP(1)\n");  
                break;  
            case 6: printf("DROP(2)\n");  
                break;  
            }
        }
    }
    return 0;
}