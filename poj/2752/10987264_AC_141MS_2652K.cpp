
#include <cstdio>
#include <cstdlib>
#include <cstring>

char b[1000010];
int p[1000010];
int a[1000010];

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
        int m = strlen(b + 1);
        getp(m);
        int c = 0;
        
        int temp = m;

        while (p[temp] > 0)
        {
            temp = p[temp];
            a[c++] = temp;
        }
        for (int i = c-1; i >= 0; --i)
            printf("%d ", a[i]);
        printf("%d\n", m);
    }
    return 0;
}