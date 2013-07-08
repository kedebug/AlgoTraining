
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 50;
const int MAXC = 2 * MAXN * MAXN;

bool vis[MAXN][MAXN], succ;
char path[MAXC];
int P, Q, PC;
int dir[8][2] = {-2, -1, -2, 1, -1, -2, -1, 2, 1, -2, 1, 2, 2, -1, 2, 1};

bool judge(int x, int y) {

    if (x > 0 && x <= Q && y > 0 && y <= P && !vis[x][y]) {
        return true;
    }
    return false;
}

void dfs(int x, int y) {

    if (succ)
        return ;

    vis[x][y] = true;
    path[PC++] = x + 'A' - 1;
    path[PC++] = y + '0'; 

    if (PC == P * Q * 2) {
        succ = true ;
        return ;
    }

    for (int i = 0; i < 8; ++i) {
        int newx = x + dir[i][0];
        int newy = y + dir[i][1];

        if (judge(newx, newy) && !succ) {
            dfs(newx, newy);
            PC -= 2;
            vis[newx][newy] = false;
        }
    }
}

int main()
{
    int cases, cc = 0;
    scanf("%d", &cases);

    while (cases--) {
        scanf("%d%d", &P, &Q);

        memset(vis, false, sizeof(vis));
        memset(path, 0, sizeof(path));
        
        PC = 0, succ = false;
        dfs(1, 1);

        if (succ) {
            printf("Scenario #%d:\n%s\n\n", ++cc, path);
        } else {
            printf("Scenario #%d:\nimpossible\n\n", ++cc);
        }
    }
    return 0;
}