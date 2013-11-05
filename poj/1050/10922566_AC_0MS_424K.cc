
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int maxn = 110;

int an[maxn][maxn];

int max_sub_array(int b[], int n)
{
    int i;
    int max = -1000000, temp = 0;
    for (i = 0; i < n; ++i)
    {
        temp += b[i];
        if (max < temp)
            max = temp;
        if (temp < 0)
            temp = 0;
    }
    return max;
}

int max_sub_matrix(int m, int n)
{
    int i, j, k;
    int b[maxn];
    int maxsum = -10000000, sum;

    for (i = 0; i < m; ++i)
    {
        memset(b, 0, sizeof(b));

        for (j = i; j < m; ++j)
        {
            for (k = 0; k < n; k++)
                b[k] += an[j][k];

            sum = max_sub_array(b, n);
            if (maxsum < sum)
                maxsum = sum;
        }
    }
    return maxsum;
}

int main()
{
    int n, i, j;

    scanf("%d", &n);
    
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            scanf("%d", &an[i][j]);

    printf("%d\n", max_sub_matrix(n, n));
    return 0;
}