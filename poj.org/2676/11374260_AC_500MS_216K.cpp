#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <set>
#include <Map>
#include <utility>
#include <queue>
#include <stack>
#include <list>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <ctype.h>
using namespace std;

char Map[15][15];
bool row[15][15], col[15][15], cube[15][15][15], flag;    //存在性表
int find (int x)    //寻找所在九宫格的坐标
{
	if (x < 3)
		return 0;
	if (x < 6)
		return 1;
	return 2;
}
void dfs (int times)    //times是扫描次数
{
	if (flag)
		return ;
	if (times >= 81)    //扫描完全部，就代表填完数了
	{
		flag = true;
		return ;
	}
	int h, k, x, y, i;
	h = times / 9;
	k = times % 9;    //求出扫描第times次时的格子坐标
	if (Map[h][k] != '0')
	{
		dfs (times+1);    //已经有数，扫描下一个
		return ;
	}
	x = find(h);
	y = find(k);
	for (i = 1; i <= 9; i++)
	{
		if (!row[h][i] && !col[k][i] && !cube[x][y][i])
		{         //第h行是否存在i，第k列是否存在i，第（x，y）个九宫格是否存在i
			row[h][i] = col[k][i] = cube[x][y][i] = true;
			Map[h][k] = i + '0';
			/*printf ("0-----\n");    //打表调试
			for (int j = 0; j < 9; j++)
				cout << Map[j] << endl;
			printf ("\n");*/
			dfs (times+1);
			if (flag)
				return ;
			row[h][i] = col[k][i] = cube[x][y][i] = false;
			Map[h][k] = '0';   //回溯
		}
	}
	return ;
}

int main()
{
	int i, j, x, y, t;
	cin >> t;
	getchar();
	while (t--)
	{
		memset (row, false, sizeof(row));
		memset (col, false, sizeof(col));
		memset (cube, false, sizeof(cube));
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				scanf ("%c", &Map[i][j]);
				if (Map[i][j] != '0')
				{
					row[i][Map[i][j]-'0'] = true;
					col[j][Map[i][j]-'0'] = true;
					x = find(i);
					y = find(j);
					cube[x][y][Map[i][j]-'0'] = true;
				}
			}
			getchar();
		}
		flag = false;
		dfs (0);
		for (i = 0; i < 9; i++)
			printf ("%s\n", Map[i]);
	}
	return 0;
}
