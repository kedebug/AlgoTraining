
#include <cstdio>
#include <cstdlib>
#include <cstring>

char b[1000010];
int p[1000010];

void getp(int m)
{
    p[1] = 0;
    int j = 0;
    for (int i = 2; i <= m; ++i)
    {
        while (j > 0 && b[j+1] != b[i])
            j = p[j];
        if (b[j+1] == b[i])
            ++j;
        p[i] = j;
    }
}

int main()
{
    while (scanf("%s", b + 1) != EOF)
    {
        if (b[1] == '.')
            break;
        int m = strlen(b + 1);
        getp(m);
        if (m % (m-p[m]) == 0)
            printf("%d\n", m/(m-p[m]));
        else
            printf("1\n");
    }
    return 0;
}