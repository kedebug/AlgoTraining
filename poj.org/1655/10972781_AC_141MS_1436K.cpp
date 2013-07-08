#include<stdio.h>
#include<string.h>
#include<vector>
#define MAX(a,b) a > b ? a : b ;
#define MAXN 20010
using namespace std;
int Tc ,N ;
vector<int> G[MAXN] ;
int f[MAXN] ;
int balance[MAXN] ;

inline void Init(){
	for(int i=1;i<=N;i++){
		G[i].clear() ;
		f[i] = -1 ;
	}	
} 
void build(int u){//<span style="white-space:pre"></span>//建树
	for(int i=0;i<G[u].size();i++){
		int v = G[u][i] ;	
		if(v == f[u])	continue ;
		f[v] = u ;
		build(v) ;
	}
}
int dfs(int u){
	int _max = 0 ,sum = 0 ;
	for(int i=0;i<G[u].size();i++){
		int v = G[u][i] ;
		if(v == f[u])	continue ;
		int res1 = dfs(v);
		sum += res1 ;
		_max = MAX(_max , res1 );	
	}	
	_max = MAX(_max ,N-sum-1);
	balance[u] = _max ;
	return sum + 1 ;
}
int main(){
	int a ,b ;
	scanf("%d",&Tc);
	while(Tc--){
		scanf("%d",&N);
		Init();
		for(int i=1;i<N;i++){
			scanf("%d %d",&a,&b);	
			G[a].push_back(b) ;
			G[b].push_back(a) ;
		}
		build(1) ;
		dfs(1);
		int _min = MAXN ,min_n;
		for(int i=1;i<=N;i++){
			if(_min > balance[i]){
				_min = balance[i] ;
				min_n = i ;	
			}
		}
		printf("%d %d\n",min_n ,_min);
	}
	return 0;	
}
