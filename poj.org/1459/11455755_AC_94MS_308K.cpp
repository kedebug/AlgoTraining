#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

#define N 210
#define MAX 9999999
#define CLR(arr, what) memset(arr, what, sizeof(arr))

int maze[N][N]; //残留网络
int pre[N], cur[N]; //前驱、后继
int gap[N]; //层结点数（用于间隙优化）
int dis[N]; //到汇点的最少弧的数目
int source, sink, nodenum; //源点、汇点、总结点数

int SAP(int s, int t, int n) //源点、汇点、结点数
{
	CLR(gap, 0); CLR(cur, 0); CLR(dis, 0);
	int u = pre[s] = s, maxflow = 0, aug = MAX, v;
	gap[0] = n;
	while(dis[s] < n)
	{
		bool flag = false;
		for(v = cur[u]; v <= n; ++v) //寻找允许弧
		{
			if(maze[u][v] > 0 && dis[u] == dis[v] + 1)
			{
				flag = true;
				break;
			}
		}
		if(flag) //找到允许弧
		{
			pre[v] = u;
			cur[u] = v;
			aug = min(aug, maze[u][v]);
			u = v;
			if(v == t) //找到完整增广路
			{
				maxflow += aug;
				for(v = t; v != s; v = pre[v]) //更新残留网络
				{
					maze[pre[v]][v] -= aug; //正向边
					maze[v][pre[v]] += aug; //反向边
				}
				aug = MAX, u = s; //重新从源点寻找
			}
		}
		else //找不到允许弧
		{
			int mindis = n;
			for(v = 1; v <= n; ++v) //重新标号
			{
				if(maze[u][v] && mindis > dis[v])
				{
					cur[u] = v;
					mindis = dis[v];
				}
			}
			if(--gap[dis[u]] == 0) //更新断层 + 判断是否断层（间隙优化）
				break;
			gap[dis[u] = mindis + 1]++; //更新断层
			u = pre[u]; //当前弧优化
		}
	}
	return maxflow;
}

int main()
{
	int power, consumer, link;
	int start, end, cost;
	int answer;
	while(scanf("%d", &nodenum) != EOF)
	{
		CLR(maze, 0);
		scanf("%d%d%d", &power, &consumer, &link);
		for(int i = 0; i < link; ++i)
		{
			scanf(" (%d,%d)%d ", &start, &end, &cost);
			if(start == end)
				continue;
			start += 2, end += 2;
			maze[start][end] += cost;
		}
		for(int i = 0; i < power; ++i) //超级源点
		{
			scanf(" (%d)%d ", &end, &cost);
			end += 2;
			maze[1][end] += cost;
		}
		for(int i = 0; i < consumer; ++i) //超级汇点
		{
			scanf(" (%d)%d ", &start, &cost);
			start += 2;
			int res = nodenum + 2;
			maze[start][res] += cost;
		}
		answer = SAP(1, nodenum + 2, nodenum + 2);
		printf("%d\n", answer);
	}
	return 0;
}