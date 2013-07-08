
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 362880 + 10;
const int fac[15] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
const char dir[5] = {0, 'u', 'd', 'l', 'r'};
const int dis[9][2] = {{0,0}, {0,1}, {0,2}, {1,0}, {1,1}, {1,2}, {2,0}, {2,1}, {2,2}};

bool vis[MAXN];
int F[MAXN], ENDS;
char OP[MAXN];

struct ST {
    char e[10];
    int f, step;
    bool operator < (const ST& other) const {
        return f > other.f;
    }
};

struct PATH {
    int op, pre;
    PATH(int _op, int _pre) : op(_op), pre(_pre) {}
};

int getvalue(const char e[]) {
    int ans = 0, count;
    for (int i = 0; i < 8; i++) {
        count = 0;
        for (int j = i + 1; j < 9; j++) {
            if (e[i] > e[j]) count += 1;
        }
        ans += fac[8-i] * count;
    }
    return ans;
}

bool challenge(ST& s, int pos, int op) {
    if (op == 1) {
        // up
        if (pos >= 3) {
            swap(s.e[pos-3], s.e[pos]);
            return true;
        }
    } else if (op == 2) {
        // down
        if (pos < 6) {
            swap(s.e[pos], s.e[pos+3]);
            return true;
        }
    } else if (op == 3) {
        // left
        if (pos % 3) {
            swap(s.e[pos-1], s.e[pos]);
            return true;
        }
    } else if (op == 4) {
        // right
        if ((pos + 1) % 3) {
            swap(s.e[pos], s.e[pos+1]);
            return true;
        }
    }
    return false;
}

int getdiff(const char e[]) {
    int ret = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int k = 3 * i + j;
            if (e[k] != 9) {
                ret += abs(i - dis[e[k]-1][0]) + abs(j - dis[e[k]-1][1]);
            }
        }
    }
    return ret;
}

bool judge(const char e[]) {
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        if (e[i] != 9) {
            for (int j = i + 1; j < 9; j++)
                if (e[i] > e[j])  sum += 1;
        }
    }
    return !(sum & 0x01);
}

bool bfs(ST& s) {
    priority_queue<ST> Q;

    s.step = 0;
    s.f = s.step + getdiff(s.e);

    Q.push(s);
    
    int vals = getvalue(s.e);
    F[vals] = -1;
    OP[vals] = 0;
    vis[vals] = true;

    while (!Q.empty()) {
        ST u = Q.top();
        Q.pop();

        int pos;
        for (int i = 0; i < 9; i++)
            if (u.e[i] == 9) pos = i;

        for (int i = 1; i <= 4; i++) {
            ST v = u;
            if (challenge(v, pos, i)) {
                int state = getvalue(v.e);
                if (!vis[state] && judge(v.e)) {
                    vis[state] = true;
                    v.step = u.step + 1;
                    v.f = v.step + getdiff(v.e);
                    Q.push(v);

                    F[state] = getvalue(u.e);
                    OP[state] = dir[i];

                    if (state == ENDS)
                        return true;
                }
            }
        }
    }
    return false;
}

int main() {
    ST u, E;
    for (int i = 0; i < 9; i++)
        E.e[i] = i + 1;
    ENDS = getvalue(E.e);

    char ch[100];
    while (gets(ch)) {
        for (int i = 0, j = 0; ch[i]; i++) {
            if (ch[i] != ' ') {
                if (ch[i] == 'x')
                    u.e[j++] = 9;
                else
                    u.e[j++] = ch[i] - '0';
            }
        }

        if (getvalue(u.e) == ENDS) {
            //printf("lr\n");
            continue;
        }

        int j = 0;
        char opcode[1000];

        memset(vis, false, sizeof(vis));
        memset(F, -1, sizeof(F));
        memset(OP, 0, sizeof(OP));

        if (judge(u.e) && bfs(u)) {
            for (int i = ENDS; i != -1; i = F[i])
                opcode[j++] = OP[i];
            for (int i = j-2; i >= 0; i--)
                printf("%c", opcode[i]);
            printf("\n");
        } else {
            printf("unsolvable\n");
        }
    }
    return 0;
}