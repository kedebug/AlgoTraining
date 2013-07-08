
//
// http://blog.csdn.net/lijiecsu/article/details/7579855
// 
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int INF = 0x7FFF;
int king_move[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};  
int knight_move[8][2] = {{-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1}};
int king_map[65][65], knight_map[65][65];

bool judge(int x, int y)   
{  
    if(x >= 0 && x < 8 && y >= 0 && y < 8) 
        return true;  
    else 
        return false;  
}  

void init()
{
    int i, j;
    int x, y, tx, ty;
    for (i = 0; i < 64; ++i)
    {
        for (j = 0; j < 64; ++j)
            knight_map[i][j] = INF, king_map[i][j] = INF;

        knight_map[i][i] = 0; 
        king_map[i][i] = 0;

        x = i % 8; y = i / 8;

        for (j = 0; j < 8; ++j)
        {
            tx = x + king_move[j][0];
            ty = y + king_move[j][1];

            if (judge(tx, ty))
                king_map[i][tx+ty*8] = 1;

            tx = x + knight_move[j][0];
            ty = y + knight_move[j][1];

            if (judge(tx, ty))
                knight_map[i][tx+ty*8] = 1;
        }
    }
}

void floyd()
{
    int i, j, k;
    for (k = 0; k < 64; ++k)
    {
        for (i = 0; i < 64; ++i)
        {
            for (j = 0; j < 64; ++j)
            {
                if (king_map[i][j] > king_map[i][k] + king_map[k][j])
                    king_map[i][j] = king_map[i][k] + king_map[k][j];

                if (knight_map[i][j] > knight_map[i][k] + knight_map[k][j])
                    knight_map[i][j] = knight_map[i][k] + knight_map[k][j];
            }
        }
    }
}

int main()
{
    char s[256];
    int pos[65];
    int i, j, num;

    memset(s, 0, sizeof(s));
    init();
    floyd();

    scanf("%s", s);
    for (i = 0, num = 0; i < strlen(s); i += 2)
        pos[num++] = s[i] - 'A' + (s[i+1] - '1') * 8;

    int min_move = INF;
    int dst, met, k, sum;
    // the position is range from 0 to 63
    for (dst = 0; dst < 64; ++dst)
    {
        for (met = 0; met < 64; ++met)
        {
            for (k = 1; k < num; ++k)
            {
                sum = 0;
                for (i = 1; i < num; ++i)
                    sum += knight_map[pos[i]][dst];

                sum += king_map[pos[0]][met];
                sum += knight_map[pos[k]][met] + knight_map[met][dst];
                sum -= knight_map[pos[k]][dst];

                if (sum < min_move)
                    min_move = sum;
            }
        }
    }
    printf("%d\n", min_move);
    return 0;
}