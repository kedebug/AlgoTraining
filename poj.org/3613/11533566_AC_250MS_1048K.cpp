
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

const int MAXN = 210;

class Matrix {
public:
    int e[MAXN][MAXN], n;

    void setn(int n) { this->n = n; }
    void initvalue() { memset(e, 0x3F, sizeof(e)); }

    Matrix operator = (const Matrix& o) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) 
                e[i][j] = o.e[i][j];
        return *this;
    }
    Matrix operator * (const Matrix& o) {
        Matrix m;
        m.initvalue();
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)
                m.e[i][j] = min(m.e[i][j], e[i][k] + o.e[k][j]);
        return m;
    }
};

Matrix M1, M2;
map<int, int> my;

int main() {
    int n, t, s, e;
    while (~scanf("%d%d%d%d", &n, &t, &s, &e)) {
        int cflag = 0;
        M1.initvalue(); 
        M2.initvalue();
        for (int i = 0; i < t; i++) {
            int cost, u, v;
            scanf("%d%d%d", &cost, &u, &v);
            if (!my[u]) my[u] = ++cflag;
            if (!my[v]) my[v] = ++cflag;
            int a = my[u], b = my[v];
            M1.e[a][b] = M1.e[b][a] = cost;
        }
        for (int i = 1; i <= cflag; i++)
            M2.e[i][i] = 0;

        M1.setn(cflag), M2.setn(cflag);

        while (n) {
            if (n & 1)
                M2 = M1 * M2;
            M1 = M1 * M1;
            n >>= 1;
        }

        printf("%d\n", M2.e[my[s]][my[e]]);
    }
    return 0;
}