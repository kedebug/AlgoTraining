#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,gp[9][9],sum[9][9][9][9],dp[16][9][9][9][9];
void init()
{
	for(int x=0;x<9;x++)
		for(int y=0;y<9;y++)
			for(int xx=x;xx<9;xx++)
				for(int yy=y;yy<9;yy++)
				{
					int ans=0;
					for(int i=x;i<=xx;i++)
						for(int j=y;j<=yy;j++)
						{
							ans+=gp[i][j];
						}
						sum[x][y][xx][yy]=ans*ans;
						
				}
}
int DP(int k,int x,int y,int xx,int yy)
{
	if(dp[k][x][y][xx][yy]>=0) return dp[k][x][y][xx][yy];
	if(k==n-1)return sum[x][y][xx][yy];
	int ans=0;
	dp[k][x][y][xx][yy]=1<<29;
	for(int i=x;i<xx;i++)
	{
		ans=min(DP(k+1,x,y,i,yy)+sum[i+1][y][xx][yy],DP(k+1,i+1,y,xx,yy)+sum[x][y][i][yy]);
		dp[k][x][y][xx][yy]=min(ans,dp[k][x][y][xx][yy]);
	}
	for(int i=y;i<yy;i++)
	{
		ans=min(DP(k+1,x,y,xx,i)+sum[x][i+1][xx][yy],DP(k+1,x,i+1,xx,yy)+sum[x][y][xx][i]);
		dp[k][x][y][xx][yy]=min(ans,dp[k][x][y][xx][yy]);
	}
	return dp[k][x][y][xx][yy];
}
int main()
{
	int cnt=0;
	double ans;
	scanf("%d",&n);
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			scanf("%d",&gp[i][j]);
			cnt+=gp[i][j];
		}
	}
	init();
	memset(dp,-1,sizeof(dp));
	DP(0,0,0,7,7);
	ans=sqrt(dp[0][0][0][7][7]*1.0/n-((cnt*1.0)/n*(cnt*1.0)/n));
	printf("%.3f\n",ans);
	return 0;
}