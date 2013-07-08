#include <iostream>
#include <cstdio>
#include <string.h>
using namespace std;

#define CLR(arr,val) memset(arr,val,sizeof(arr))
const int N = 15;
typedef long long ll;
ll dp[N][2500],ans[N][N];
int row,col;
void init(int num,int id){
	if(id == col){
	  dp[0][num]++;
	  return;
	}
	if(id < col){
	  init(num<<1,id+1);
	}
	if(id + 1 < col)
		init(num<<2|3,id+2);
}
void dfs(int x,int xstate,int upstate,int id){
	if(id >= col){
	  dp[x][xstate] += dp[x-1][upstate];
	  return;
	}
	if(id < col){
	  dfs(x,xstate<<1,upstate<<1|1,id+1);
	  dfs(x,xstate<<1|1,upstate<<1,id+1);
	}
	if(id+1 < col)
		dfs(x,xstate<<2|3,upstate<<2|3,id+2);
}
int main(){
	CLR(ans,-1,sizeof(ans));
	while(scanf("%d%d",&row,&col) && row && col){
		if(ans[row][col] != -1){
		  printf("%lld\n",ans[row][col]);
		  continue;
		}
		if((row * col)%2){
		  printf("0\n");
		  continue;
		}
		if(col > row){
		  int t = row;
		  row = col;
		  col = t;
		}
		CLR(dp,0);
		init(0,0);
		for(int i = 1;i < row;++i){
		  dfs(i,0,0,0);
		}
		ans[row][col] = ans[col][row] = dp[row-1][(1<<col)-1];
		printf("%lld\n",ans[row][col]);
	}
	return 0;
}