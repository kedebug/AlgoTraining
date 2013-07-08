
#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
using namespace std;

const int MAXN = 362880 + 10;
const int fac[20] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
const char dir[5] = {0, 'u', 'd', 'l', 'r'};

bool vis[MAXN];

struct ST {
    char e[10];
};

struct PATH {
    int op, pre;
    PATH(int _op, int _pre) : op(_op), pre(_pre) {}
};

int getpos(const ST& s) {
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

bool work(ST& s, int pos, int op) {
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

bool bfs(const ST& s, vector<PATH>& P) {
    deque<ST> Q;
    Q.push_back(s);
    P.clear();
    P.push_back(PATH(-1, -1));
    vis[getpos(s)] = true;

    ST E;
    for (int i = 0; i < 9; i++)
        E.e[i] = i + 1;
    int dst = getpos(E);

    int count = -1;
    while (!Q.empty()) {
        count += 1;
        ST u = Q.front();
        Q.pop_front(); 

        int pos;
        for (int i = 0; i < 9; i++)
            if (u.e[i] == 9) pos = i;

        for (int i = 1; i <= 4; i++) {
            ST v = u;
            if (work(v, pos, i)) {
                int num = getpos(v);
                if (!vis[num]) {
                    vis[num] = true;
                    Q.push_back(v);
                    P.push_back(PATH(i, count));
                    if (num == dst)
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
    vector<PATH> P;
    vector<int> op;

    if (bfs(u, P)) {
        for (i = P.size()-1; i != 0; i = P[i].pre)
            op.push_back(P[i].op);
        for (i = op.size()-1; i >= 0; i--) 
            printf("%c", dir[op[i]]);
    } else {
        printf("unsolvable\n");
    }

    return 0;
}
