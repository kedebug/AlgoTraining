
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

const int maxn = 100;
const int INF = 0x7FFFFFFF;

int maxdp[maxn][maxn];
int mindp[maxn][maxn];

int calc(int a, int b, char op)
{
    if (op == 't')
        return a + b;
    else
        return a * b;
}

int main()
{
    int n, i, j, k;
    int mmin, mmax, temp;
    int e, m1, m2;
    vector<int> v;
    char op[maxn];
    int an[maxn];

    while (scanf("%d", &n) != EOF)
    {
        for (i = 0; i < n; ++i)
        {
            getchar();
            op[i] = getchar();
            scanf("%d", &an[i]);
            maxdp[i][i] = an[i];
            mindp[i][i] = an[i];
        }
        //  k is the step of the chain
        for (k = 1; k < n; ++k)
        {
            // i is the start point
            for (i = 0; i < n; ++i)
            {
                mmax = -INF;
                mmin = INF;
                e = (i + k) % n;
                for (j = 0; j < k; ++j)
                {
                    m1 = (i + j) % n;
                    m2 = (i + j + 1) % n;

                    temp = calc(maxdp[i][m1], maxdp[m2][e], op[m2]);
                    mmax = max(mmax, temp);
                    temp = calc(mindp[i][m1], mindp[m2][e], op[m2]);
                    mmax = max(mmax, temp);

                    temp = calc(maxdp[i][m1], mindp[m2][e], op[m2]);
                    mmin = min(mmin, temp);
                    temp = calc(mindp[i][m1], maxdp[m2][e], op[m2]);
                    mmin = min(mmin, temp);
                }
                maxdp[i][e] = mmax;
                mindp[i][e] = mmin;
            }
        }
        v.clear();
        temp = -INF;
        for (i = 0; i < n; ++i)
        {
            e = (i + n - 1) % n;
            if (temp < maxdp[i][e])
            {
                temp = maxdp[i][e];
                v.clear();
                v.push_back(i);
            }
            else if (temp == maxdp[i][e])
                v.push_back(i);
        }
        printf("%d\n", temp);
        for (i = 0; i < v.size(); ++i)
            printf("%d ", v[i] + 1);
        printf("\n");
    }
    return 0;
}