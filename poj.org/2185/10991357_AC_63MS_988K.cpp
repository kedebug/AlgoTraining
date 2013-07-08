
#include <cstdio>
#include <cstdlib>
#include <cstring>

char s[10005][80];
int p[80];
int next[10005];
int f[80];

void getp(int k, int m)
{
    p[1] = 0;
    int j = 0;
    for (int i = 2; i <= m; ++i)
    {
        while (j > 0 && s[k][j+1] != s[k][i])
            j = p[j];
        if (s[k][j+1] == s[k][i])
            ++j;
        p[i] = j;

    }
}

int getp_r(int m)
{
    next[1] = 0;
    int j = 0;
    for (int i = 2; i <= m; ++i)
    {
        while (j > 0 && strcmp(s[j+1]+1, s[i]+1))
            j = next[j];
        if (!strcmp(s[j+1]+1, s[i]+1))
            ++j;
        next[i] = j;
    }
    return m - next[m];
}

int main()
{
    int r, c;
    scanf("%d %d", &r, &c);

    memset(f, 0, sizeof(f));
    for (int i = 1; i <= r; ++i)
    {
        scanf("%s", s[i] + 1);
        getp(i, c);
        int j = c;
        do {
            j = p[j];
            ++f[c-j];  
        } while (p[j]);
    }
    int i, x, y;
    for (i = 1; i < c; ++i)
        if (f[i] == r)
            break;
    x = i;
    y = getp_r(r);
    printf("%d\n", x * y);

    return 0;
}