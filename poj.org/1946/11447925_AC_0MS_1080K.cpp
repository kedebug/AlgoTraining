#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int INF = (1<<29);
int n, e, d;
int dp[25][105][105];
inline int min(int a,int b)
{
 return a < b ? a : b;
}
int main()
{
 int i, j, k;
// freopen("input.txt","r",stdin);
 while(scanf("%d %d %d",&n,&e,&d) != EOF)
 {
  for(i = 0; i <= n; ++i)
   for(j = 0; j <= d; ++j)
    for(k = 0; k <= e; ++k)
     dp[i][j][k] = INF;
  dp[1][0][0] = 0;
  for(i = 1; i <= n; ++i)
  {
   for(j = 0; j <= d; ++j)
   {
    for(k = 0; k <= e; ++k)
    {
     if(dp[i][j][k] == INF) continue; //无意义
     for(int p = 1; p+j <= d && p*p+k <= e; ++p)
      dp[i][j+p][k+p*p] = min(dp[i][j][k]+1,dp[i][j+p][k+p*p]);
     dp[i+1][j][j] = min(dp[i+1][j][j], dp[i][j][k]);
    }
   }
  }
  int result = INF;
  for(i = 0; i <= e; ++i)
   result = min(result,dp[n][d][i]);
  printf("%d\n",result); //当无法完成任务的时候dp[n][d][0] = 0;
 }
 return 0;
}