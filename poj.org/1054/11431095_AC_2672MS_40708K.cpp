#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define MOD 10007
#define MAXN 5005
using namespace std;

int R, C, N;

struct Node {
    int x, y;
}e[MAXN];

struct HASHLIST {
    int No, next;
}T[10010];

int idx, head[10010]; // hash表的头指针 
short int dp[MAXN][MAXN];

bool cmp(Node a, Node b) {
    if (a.x != b.x) return a.x < b.x;
    else return a.y < b.y;    
}

int hash(int x, int y) {
    return (x*C+y) % MOD;
}

void insert(int No, int key) {
    ++idx;
    T[idx].No = No;
    T[idx].next = head[key];
    head[key] = idx;
}

bool judge(int x, int y) {
    return x>0&&x<=R&&y>0&&y<=C;
}

int get(int x, int y) {
    int key = hash(x, y);
    for (int i = head[key]; i != -1; i = T[i].next) {
        int No = T[i].No;
        if (e[No].x == x && e[No].y == y) {
            return No;
        }
    }
    return -1;
}

int DP() {
    int nx, ny, px, py, loc;
    short ret = -1;
    for (int i = 1; i <= N; ++i) { // 枚举路径是从左上到右下角 
        for (int j = 1; j < i; ++j) { // 遍历所有节点的组合情况 
            nx = 2*e[j].x - e[i].x; // 按照i,j之间的长度计算出来的下一个节点位置
            ny = 2*e[j].y - e[i].y;
            if (judge(nx, ny)) {
                loc = get(nx, ny);
                if (loc != -1 && dp[j][loc] != -1) {
                    dp[i][j] = dp[j][loc] + 1;
                } else {
                    dp[i][j] = -1;
                }
            } else { // 表示直接跳出去了 
                dp[i][j] = 2;
            }
            px = 2*e[i].x - e[j].x;
            py = 2*e[i].y - e[j].y;
            if (!judge(px, py)) {
                ret = max(ret, dp[i][j]);
            }
        }
    }
    return ret >= 3 ? ret : 0;
}
 
int main() {
    while (scanf("%d %d", &R, &C) == 2) {
        idx = -1;
        memset(head, 0xff, sizeof (head));
        scanf("%d", &N);
        for (int i = 1; i <= N; ++i) {
            scanf("%d %d", &e[i].x, &e[i].y);
        }
        sort(e+1, e+1+N, cmp);
        for (int i = 1; i <= N; ++i) {
            insert(i, hash(e[i].x, e[i].y)); // 将这个键值插入到hash表中
        }
        printf("%hd\n", DP());
    }
    return 0;    
}