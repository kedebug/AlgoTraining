/*
POJ: 2251 Dungeon Master
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

#define M 35

using namespace std;

const int dir[6][3] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};

struct Node {
    int x, y, z;
    int step;
    
    Node (int _x, int _y, int _z, int _step) : x(_x), y(_y), z(_z), step(_step) {}
};

char map[M][M][M];
bool visited[M][M][M];
int l, r, c;
int startx, starty, startz;
queue<struct Node> que;

bool check(int x, int y, int z)
{
    if(x >= 0 && x < l && y >= 0 && y < r && z >= 0 && z < c)
        return true;
    return false;
}

int bfs(int x, int y, int z)
{
    while(!que.empty())
        que.pop();
    memset(visited, false, sizeof(visited));
    
    que.push(Node(x, y, z, 1));
    visited[x][y][z] = true;   
    while(!que.empty()) {
        struct Node tmp = que.front();
        que.pop();
        for(int i = 0; i < 6; i++) {
            int tmpx = tmp.x + dir[i][0];
            int tmpy = tmp.y + dir[i][1];
            int tmpz = tmp.z + dir[i][2];
            if(check(tmpx, tmpy, tmpz) && !visited[tmpx][tmpy][tmpz]) {
                if(map[tmpx][tmpy][tmpz] == 'E')
                    return tmp.step;
                else if(map[tmpx][tmpy][tmpz] == '.') {
                    que.push(Node(tmpx, tmpy, tmpz, tmp.step + 1));
                    visited[tmpx][tmpy][tmpz] = true;
                }
            }
        }
    }
    return -1;
}            
            
int main()
{
    //freopen("data.in", "rb", stdin);
    while(scanf("%d%d%d", &l, &r, &c) != EOF && (l || r || c)) {
        for(int i = 0; i < l; i++) {
            for(int j = 0; j < r; j++) {
                for(int k = 0; k < c; k++) {
                    char ch;
                    while(cin >> ch, ch == '\n');
                    map[i][j][k] = ch;
                    if(map[i][j][k] == 'S') {
                        startx = i;
                        starty = j;
                        startz = k;
                    }
                }
            }
        }
    
        int res = bfs(startx, starty, startz);
        if(res == -1)
            printf("Trapped!\n");
        else
            printf("Escaped in %d minute(s).\n", res);
    }

    return 0;
}