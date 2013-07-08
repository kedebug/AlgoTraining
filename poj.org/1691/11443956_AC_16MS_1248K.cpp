#include <iostream>
using namespace std;

#define N 16
#define INF 99999

int m, n;
int dp[1<<N][N], up[N]; 
/* dp[s][i]表示：最后一次给矩形i涂色，得到s状态所需要的最小次数 */
/* up[i] 记录矩形i上面相邻的矩形 */

struct Rectangle
{
	int x1, x2, y1, y2, color;
} rec[N];

bool check ( int i, int j )
{
	if ( rec[i].y2 != rec[j].y1 ) return false;
	if ( rec[i].x2 <= rec[j].x1 ) return false;
	if ( rec[i].x1 >= rec[j].x2 ) return false;
	return true;
}

void build_map()
{
	memset(up,0,sizeof(up));
	for ( int i = 0; i < n ; i++ )
	{
		for ( int j = 0; j < n; j++ )
			if ( check ( i, j ) )
			    up[j] |= ( 1 << i );  /* 记录每个矩形上面相邻的矩形 */
	}
}

int operDp ()
{
	int s, i, j;
	int newSt, temp, State;

	State = (1<<n)-1;
	for ( s = 0; s <= State; s++ )
		for ( j = 0; j < n; j++ )
			dp[s][j] = INF;

	for ( i = 0; i < n; i++ )
		if ( up[i] == 0 ) /* 初始化，即处理位于最上面的那一排矩形*/
			dp[1<<i][i] = 1;

	for ( s = 0; s <= State; s++ )
	{
		for ( i = 0; i < n; i++ ) /* 从1-n中筛选出没有被涂色的矩形i，然后给i涂色 */
		{
			if ( s & (1<<i) ) continue; // 矩形i已经被涂色continue
			if ( (s & up[i]) != up[i] ) continue; // 矩形i上面还有没被涂色的矩形continue

			for ( j = 0; j < n; j++ ) /*枚举得到s状态时最后涂色的那一个矩形（因为最后涂色的矩形不同，所用的刷子颜色也不同）*/
			{
				if ( (s & (1<<j)) == 0 ) continue; //矩形j还没有被涂色continue
				newSt = (s | (1<<i));
				temp = dp[s][j];  
				if ( rec[i].color != rec[j].color ) temp++;
				if ( temp < dp[newSt][i] ) dp[newSt][i] = temp;
			}
		}
	}

	temp = INF;
	for ( i = 0; i < n; i++ )
		if ( dp[State][i] < temp )
			temp = dp[State][i];
	return temp;
}



int main()
{
	cin >> m;
	while ( m-- )
	{
		cin >> n;
		for ( int i = 0; i < n; i++ )
			cin >> rec[i].y1 >> rec[i].x1 >> rec[i].y2 >> rec[i].x2 >> rec[i].color;

		build_map();
		int ans = operDp();
		cout << ans << endl;
	}
	return 0;
}
