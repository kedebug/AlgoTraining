#include <iostream>
#include <cstdio>
#include <cstring>

#define N 16
#define M 5000
#define C 1025
#define R 2048
using namespace std;

int num[N][N];
bool map[R][C];
int l[M], r[M], u[M], d[M], c[M], s[M], x[M], y[M], z[M], f[M];
int turn[R][C];
int n, all, head;

int block(int i, int j)
{
    return (i/4)*4 + j/4;
}

void build(void)
{
    int i, j, k;
    int temp;

    memset(s, 0, sizeof(s));

    for (all=0; all<C; all++)
        c[all] = all;

    for (i=0; i<n; i++)
        for (j=0; j<C; j++)
            if (map[i][j])
            {
                s[j]++;
                c[all] = j;
                f[all] = i;
                turn[i][j] = all;
                all++;
            }

    for (i=0; i<n; i++)
        for (j=0; j<C; j++)
            if (map[i][j])
            {
                temp = turn[i][j];

                for (k=j-1; k>=0 && !map[i][k]; k--);
                if (k == -1)
                    for (k=C-1; !map[i][k]; k--);
                l[temp] = turn[i][k];
                r[l[temp]] = temp;

                for (k=i-1; k>=0 && !map[k][j]; k--);
                if (k == -1)
                    u[temp] = j;
                else
                    u[temp] = turn[k][j];
                d[u[temp]] = temp;
                d[temp] = j;
                u[j] = temp;
            }

    head = -1;
    for (i=0; i<C; i++)
        if (s[i])
        {
            if (head == -1)
            {
                head = i;
                for (k=C-1; !s[k]; k--);
                l[i] = k;
            }
            else
                l[i] = temp;

            r[l[i]] = i;
            temp = i;
        }
}

void move(int i)
{
    int j, k;

    if (i == head)
        head = r[head];

    l[r[i]] = l[i];
    r[l[i]] = r[i];
    for (j=d[i]; j!=i; j=d[j])
        for (k=r[j]; k!=j; k=r[k])
        {
            u[d[k]] = u[k];
            d[u[k]] = d[k];
            s[c[k]]--;
        }
}

void add(int i)
{
    int j, k;

    for (j=u[i]; j!=i; j=u[j])
        for (k=l[j]; k!=j; k=l[k])
        {
            u[d[k]] = k;
            d[u[k]] = k;
            s[c[k]]++;
        }
    l[r[i]] = i;
    r[l[i]] = i;
}

int dlx(void)
{
    int i, p, choice, temp;
    int small = 100000;

    p = head;
    if (r[p] == p)
        return 1;
    do
    {
        if (s[p] < small)
        {
            small = s[p];
            choice = p;
        }
        p = r[p];
    }while (p != head);

    if (!small)
        return 0;

    move(choice);
    for (p=u[choice]; p!=choice; p=u[p])
    {
        temp = f[p];
        num[x[temp]][y[temp]] = z[temp];

        for (i=r[p]; i!=p; i=r[i])
            move(c[i]);
        if (dlx())
            return 1;
        for (i=l[p]; i!=p; i=l[i])
            add(c[i]);
    }
    add(choice);

    return 0;
}

int main ()
{
    int i, j, k;
    int temp, b;
    bool sign[C];
    char str[32];

    while (scanf("%s", str) == 1)
    {
        memset(map, 0, sizeof(map));
        memset(sign, 0, sizeof(sign));
        n = 0;

        for (i=0; i<N; i++)
        {
            if (i)
                scanf("%s", str);
            for (j=0; j<N; j++)
            {
                if (str[j] > 'Z' || str[j] < 'A')
                    temp = 0;
                else
                    temp = (int)(str[j] - 'A' + 1);
                num[i][j] = temp;
                if (temp)
                {
                    b = block(i, j);
                    sign[i*N+j] = 1;
                    sign[N*N+i*N+temp] = 1;
                    sign[N*N*2+j*N+temp] = 1;
                    sign[N*N*3+b*N+temp] = 1;
                }
            }
        }

        for (i=0; i<N; i++)
            for (j=0; j<N; j++)
                if (!num[i][j])
                {
                    b = block(i, j);
                    for (k=1; k<=N; k++)
                        if (!sign[N*N+i*N+k] && !sign[N*N*2+j*N+k] && !sign[N*N*3+b*N+k])
                        {
                            x[n] = i;
                            y[n] = j;
                            z[n] = k;
                            map[n][i*N+j] = 1;
                            map[n][N*N+i*N+k] = 1;
                            map[n][N*N*2+j*N+k] = 1;
                            map[n][N*N*3+b*N+k] = 1;
                            n++;
                        }
                }

        build();
        if (dlx())
        {
            for (i=0; i<N; i++)
            {
                for (j=0; j<N; j++)
                    printf("%c", 'A' + (char)num[i][j] - 1);
                printf("\n");
            }
        }
        else
            printf("impossible\n");
        printf("\n");
    }
}