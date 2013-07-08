
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
int F[MAXN], END;
char OP[MAXN];

struct ST {
    char e[10];
    int f, step;
    bool operator < (const ST& other) const {
        if (f == other.f) 
            return step > other.step;
        return f > other.f;
    }
};

struct PATH {
    int op, pre;
    PATH(int _op, int _pre) : op(_op), pre(_pre) {}
};

int getvalue(const ST& s) {
    int ans = 0, count;
    for (int i = 0; i < 8; i++) {
        count = 0;
        for (int j = i + 1; j < 9; j++) {
            if (s.e[i] > s.e[j]) count += 1;
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

bool bfs(ST& s) {
    priority_queue<ST> Q;

    s.step = 0;
    s.f = s.step + getdiff(s.e);

    Q.push(s);
    
    int vals = getvalue(s);
    F[vals] = -1;
    OP[vals] = 0;
    vis[vals] = true;

    int count = -1;
    while (!Q.empty()) {
        count += 1;
        ST u = Q.top();
        Q.pop();

        int pos;
        for (int i = 0; i < 9; i++)
            if (u.e[i] == 9) pos = i;

        for (int i = 1; i <= 4; i++) {
            ST v = u;
            if (challenge(v, pos, i)) {
                int num = getvalue(v);
                if (!vis[num]) {
                    vis[num] = true;
                    v.step = u.step + 1;
                    v.f = v.step + getdiff(v.e);
                    Q.push(v);

                    F[num] = getvalue(u);
                    OP[num] = dir[i];

                    if (num == END)
                        return true;
                }
            }
        }
    }
    return false;
}

int main() {
    char ch;
    ST u;
    int i = 0;

    while (scanf("%c", &ch) != EOF) {
        if (ch != ' ') {
            if (ch == 'x')
                u.e[i++] = 9;
            else
                u.e[i++] = ch - '0';
        }
    }

    //u.e[0] = 2;
    //u.e[1] = 3; u.e[2] = 4, u.e[3] = 1;
    //u.e[4] = 5, u.e[5] = 9, u.e[6] = 7;
    //u.e[7] = 6; u.e[8] = 8;

    ST E;
    for (int i = 0; i < 9; i++)
        E.e[i] = i + 1;
    END = getvalue(E);

    int j = 0;
    char opcode[100];

    if (bfs(u)) {
        for (int i = 0; i != -1; i = F[i])
            opcode[j++] = OP[i];
        for (int i = j-2; i >= 0; i--)
            printf("%c", opcode[i]);
    } else {
        printf("unsolvable\n");
    }

    return 0;
}
