
#include <cstdio>
#include <cstring>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 32;

struct Matrix {
    int v[MAXN][MAXN];
} ;

int n, M;

Matrix matrixadd(Matrix a, Matrix b)
{
    Matrix c;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            c.v[i][j] = (a.v[i][j] + b.v[i][j]) % M;
    return c;
}

Matrix matrixmul(Matrix a, Matrix b)
{
    Matrix c;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            c.v[i][j] = 0;
            for (int k = 0; k < n; ++k)
                c.v[i][j] = (a.v[i][k] * b.v[k][j] + c.v[i][j]) % M;
        }
    return c;
}

Matrix matrixpow(Matrix m, int k)
{
    if (k == 1)
        return m;

    Matrix c;
    c = matrixpow(m, k >> 1);
    c = matrixmul(c, c);

    if (k % 2)
        c = matrixmul(c, m);
    return c;
}

Matrix matrixcalc(Matrix m, int k)
{
    if (k == 1)
        return m;

    Matrix a, b, c;

    a = matrixcalc(m, k >> 1);

    if (k % 2) {
        b = matrixpow(m, (k+1)>>1);
        c = matrixadd(matrixadd(a, b), matrixmul(a, b));
    } else {
        b = matrixpow(m, k >> 1);
        c = matrixmul(a, b);
        c = matrixadd(a, c);
    }

    return c;
}

int main()
{
    Matrix m;
    int k;
    scanf("%d %d %d", &n, &k, &M);

    memset(m.v, 0, sizeof(m.v));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", &m.v[i][j]);

    m = matrixcalc(m, k);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%d ", m.v[i][j]);
        printf("\n");
    }
	return 0;
}