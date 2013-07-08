#pragma warning (disable:4786)  
#include<iostream>
#include<queue>
using namespace std;
int n;
__int64 dp[101][201];
int main(){
	int i, j;
	while( scanf("%d", &n) && n ){		
		memset( dp, 0, sizeof( dp ) );
		dp[0][1] = 1;
		int model = 1;
		__int64 pos = 1;
		for( i = 1; i <= 100; i ++ ){   //此处100 是因为题目保证结果位数不超过100
			pos = pos * 10;
			model = ( model * 10 ) % n;
			for( j = 0; j < 200; j ++ )
				dp[i][j] = dp[i - 1][j];	
			for( j = 0; j < 200; j ++ ){
				if( dp[i - 1][j] != 0 || j == 0 ){
					int mm = ( model + j ) % n;
					if( dp[i][mm] == 0 )
						dp[i][mm] = pos + dp[i - 1][j];
					if( mm == 0 ){
						printf( "%I64d\n",dp[i][mm] );
						i = 100;
						break;
					}
				}
			}
		}
	}
	return 0;
}