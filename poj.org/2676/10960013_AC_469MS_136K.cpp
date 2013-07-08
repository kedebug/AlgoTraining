
#include <cstdio>
#include <cstdlib>
#include <cstring>

int mat[10][10];
bool row[10][10];
bool col[10][10];
bool grid[10][10];

bool dfs(int i, int j)
{
    if (i == 9)
        return true;

    bool flag = false;
    if (mat[i][j])
    {
        if (j == 8)
            flag = dfs(i+1, 0);
        else
            flag = dfs(i, j+1);

        if (flag)
            return true;
        else
            return false;
    }
    else
    {
        int n, k;
        k = (i/3)*3 + j/3;
        for (n = 1; n <= 9; ++n)
        {
            if(!row[i][n] && !col[j][n] && !grid[k][n])
            {
                mat[i][j] = n;
                row[i][n] = true;
                col[j][n] = true;
                grid[k][n] = true;

                if (j == 8)
                    flag = dfs(i+1, 0);
                else
                    flag = dfs(i, j+1);

                if (flag)
                    return true;

                mat[i][j] = 0;
                row[i][n] = false;
                col[j][n] = false;
                grid[k][n] = false;
            }
        }
    }
    return false;
}

int main()
{
    int t;
    char s[16];
    scanf("%d", &t);
    while (t--)
    {
        int i, j;
        int n;

        memset(row, false, sizeof(row));
        memset(col, false, sizeof(col));
        memset(grid, false, sizeof(grid));
        memset(mat, 0, sizeof(mat));

        for (i = 0; i < 9; ++i)
        {
            scanf("%s", s);
            for (j = 0; j < 9; ++j)
            {
                n = s[j] - '0';
                if (n)
                {
                    mat[i][j] = n;
                    row[i][n] = true;
                    col[j][n] = true;
                    grid[(i/3)*3+j/3][n] = true;
                }
            }
        }
        dfs(0, 0);
        for (i = 0; i < 9; ++i)
        {
            for (j = 0; j < 9; ++j)
                printf("%d", mat[i][j]);
            printf("\n");
        }
    }
    return 0;
}
