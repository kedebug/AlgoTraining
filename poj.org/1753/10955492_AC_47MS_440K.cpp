#include <stdio.h>  
#include <queue>  
using namespace std;  
#define N 17  
#define MAXN (1<<16)  
int bit[N];  
int vis[MAXN],src;  
int move[5][2] = {0,0,0,1,1,0,0,-1,-1,0};  
int bfs()  
{  
    if(src == 0 || src == (MAXN - 1))  
        return 0;  
    queue<int> que;  
    que.push(src);  
    vis[src] = 1;  
    int i,j,k,x,y,p,pt;  
    while(!que.empty())  
    {  
        p = que.front();  
        que.pop();  
        for(i = 0; i < 4; ++i)  
            for(j = 0; j < 4; ++j)  
            {  
                pt = p;  
                for(k = 0; k < 5; ++k)  
                {  
                    x = i + move[k][0];  
                    y = j + move[k][1];  
                    if(x >= 0 && x < 4 && y >= 0 && y < 4)  
                        pt ^= bit[x * 4 + y];  
                }  
                if(pt == 0 || pt == MAXN - 1)  
                    return vis[p];  
                if(vis[pt] == 0)  
                {  
                    vis[pt] = vis[p] + 1;  
                    que.push(pt);  
                }  
            }  
    }  
    return -1;  
}  
int main()  
{  
    char mat[5][5];  
    int i,j;  
    for(i = 0; i < N; ++i)  
        bit[i] = 1 << i;  
    src = 0;  
    for(i = 0; i < 4; ++i)  
    {  
        scanf("%s",mat[i]);  
        for(j = 0; j < 4; ++j)  
            if(mat[i][j] == 'b')  
                src |= bit[i * 4 + j];  
    }  
    int res = bfs();  
    printf(res == -1 ? "Impossible\n":"%d\n",res);  
    return 0;  
}  
