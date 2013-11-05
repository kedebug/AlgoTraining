
#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
using namespace std;

const int MAXN = 110;

struct ST {
    int a, b, step;
    ST(int _a, int _b, int _d) : a(_a), b(_b), step(_d) {}
};

struct PATH {
    int op, pre;
    PATH(int _op, int _pre) : op(_op), pre(_pre) {}
};

int A, B, C;
bool vis[MAXN][MAXN];

inline bool judge(int a, int b) {
    if (a == C || b == C) {
        return true;
    } 
    return false;
}

int bfs(vector<PATH>& P) {
    deque<ST> Q;
    Q.push_back(ST(0, 0, 0));
    P.push_back(PATH(-1, -1));
    vis[0][0] = true;

    int cflag = -1;
    while (!Q.empty()) {
        cflag += 1;
        ST s = Q.front();
        Q.pop_front();

        // fill a, op = 1
        if (!vis[A][s.b]) {
            vis[A][s.b] = true;
            Q.push_back(ST(A, s.b, s.step + 1));
            P.push_back(PATH(1, cflag));
            if (judge(A, s.b)) return s.step + 1;
        }
        // drop a, op = 2
        if (!vis[0][s.b]) {
            vis[0][s.b] = true;
            Q.push_back(ST(0, s.b, s.step + 1));
            P.push_back(PATH(2, cflag));
            if (judge(0, s.b)) return s.step + 1;
        }
        // fill b, op = 3
        if (!vis[s.a][B]) {
            vis[s.a][B] = true;
            Q.push_back(ST(s.a, B, s.step + 1));
            P.push_back(PATH(3, cflag));
            if (judge(s.a, B)) return s.step + 1;
        }
        // drop b, op = 4
        if (!vis[s.a][0]) {
            vis[s.a][0] = true;
            Q.push_back(ST(s.a, 0, s.step + 1));
            P.push_back(PATH(4, cflag));
            if (judge(s.a, 0)) return s.step + 1;
        }
        int a, b;
        // pour(a, b), op = 5
        if (s.a + s.b <= B) {
            a = 0, b = s.a + s.b;
        } else {
            a = s.a + s.b - B, b = B;
        }
        if (!vis[a][b]) {
            vis[a][b] = true;
            Q.push_back(ST(a, b, s.step + 1));
            P.push_back(PATH(5, cflag));
            if (judge(a, b)) return s.step + 1;
        }
        // pour(b, a), op = 6
        if (s.a + s.b <= A) {
            a = s.a + s.b, b = 0;
        } else {
            a = A, b = s.a + s.b - A;
        }
        if (!vis[a][b]) {
            vis[a][b] = true;
            Q.push_back(ST(a, b, s.step + 1));
            P.push_back(PATH(6, cflag));
            if (judge(a, b)) return s.step + 1;
        }
    }
    return -1;
}

int main() {
    scanf("%d%d%d", &A, &B, &C);
    vector<PATH> P;
    int ans = bfs(P);
    if (ans == -1) {
        printf("impossible\n");
    } else {
        printf("%d\n", ans);
        vector<int> v;
        for (int i = P.size()-1; i != -1; i = P[i].pre) {
            v.push_back(P[i].op);
        }
        for (int i = v.size()-1; i >= 0; i--) {
            if (v[i] == 1)
                printf("FILL(1)\n");
            else if (v[i] == 2)
                printf("DROP(1)\n");
            else if (v[i] == 3)
                printf("FILL(2)\n");
            else if (v[i] == 4)
                printf("DROP(2)\n");
            else if (v[i] == 5)
                printf("POUR(1,2)\n");
            else if (v[i] == 6)
                printf("POUR(2,1)\n");
        }
    }
    return 0;
}