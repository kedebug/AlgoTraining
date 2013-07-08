#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
#define MAXN 30
struct cnode
{
  int x;
  int y;
  int MapToPoint;// the index of point 
  char ch;
}node[MAXN][MAXN];
struct cpoint
{
  int x;
  int y;
}point[MAXN];
int dir[][2] = {{-1,0},{0,-1},{0,1},{1,0}};
bool visit[MAXN][MAXN];
int step[MAXN][MAXN];//the distance between two point
int ans;
int SumStep[MAXN][MAXN];//note the distance of all the points from the start point in the BFS
void bfs(cpoint p,int INDEX)
{
  
  queue<cpoint> qu;
  qu.push(p);
  cpoint current;
  cpoint jump;
  int i;
  
  while(!qu.empty())
    {
      current = qu.front();
      qu.pop();
      for(i = 0;i < 4;i++)
	{
	  jump.x = current.x + dir[i][0];
	  jump.y = current.y + dir[i][1];
	  if(node[jump.x][jump.y].x == -1)
	    {
	      continue;
	    }
	  if(visit[jump.x][jump.y] == false)
	    {
	      visit[jump.x][jump.y] = true;
	      //cout<<"no"<<endl;
	      if(node[jump.x][jump.y].ch != 'x')
		{
		  if(node[jump.x][jump.y].ch == '*')
		    {
		      step[INDEX][ node[jump.x][jump.y].MapToPoint ] = SumStep[current.x][current.y] + 1;
		      step[ node[jump.x][jump.y].MapToPoint ][INDEX] = step[INDEX][ node[jump.x][jump.y].MapToPoint ];
		 }
		  SumStep[jump.x][jump.y] = SumStep[current.x][current.y] + 1;
		  qu.push(jump);

		}
	      
	      
	    }
	}      
    } 
}
bool DFSVisit[MAXN];
void dfs(int sx,int sy,int INDEX,int sub,int dis,int depth)
{
  if(dis > ans)
    {
      return;
    }
  int i;
  depth++;
  if(depth == sub && dis < ans)
    {
      ans = dis;
      return;
    }
  for(i = 0;i < sub;i++)
    {
      if(DFSVisit[i] == false)
	{
	  DFSVisit[i] = true;
	  dfs(point[i].x,point[i].y,i,sub,dis + step[INDEX][i],depth);
	  DFSVisit[i] = false;
	}
    }
}
int main()
{
  int n,m;
  int i;
  int j;
  int sx;
  int sy;
  int sub;
  int INDEX;
  while(scanf("%d %d",&m,&n) != EOF)
    {
      if(m == 0 && n== 0)
	{
	  break;
	}
      sub = 0;
      memset(node,255,sizeof(node));
      for(i = 1;i <= n;i++)
	{
	  getchar();
	  for(j = 1;j <= m;j++)
	    {
	      node[i][j].x = i;
	      node[i][j].y = j;
	      scanf("%c",&node[i][j].ch);
	      if(node[i][j].ch == '*')
		{
		  point[sub].x = i;
		  point[sub].y = j;
		  node[i][j].MapToPoint = sub;
		  sub++;
		  
		}
	      else if(node[i][j].ch == 'o')
		{
		  sx = i;
		  sy = j;
		  INDEX = sub;
		  point[sub].x = i;
		  node[i][j].MapToPoint = sub;
		  point[sub++].y = j;
   		}

	    }
	}
      memset(step,0,sizeof(step));
      for(i = 0; i < sub;i++)
	{
	  memset(SumStep,0,sizeof(SumStep));
	  memset(visit,false,sizeof(visit));
	  	  visit[point[i].x][point[i].y] = true;
	  bfs(point[i],i);
	}
            bool note = false;
	    for(i = 0;i < sub;i++)//if there is dity point that we can't reach ,the printf -1
	{
	  for(j = 0;j < sub;j++)
	    {
	      if(i != j && step[i][j] == 0)
		{
		  note = true;
		  printf("-1\n");
		  break;
		}
	    }
	  if(note == true)
	    {
	      break;
	    }
	  
	}
      if(note == true)
	{
	  continue;
	}
      ans = 1e9;
      memset(DFSVisit,false,sizeof(DFSVisit));
      DFSVisit[INDEX] = true;
      dfs(sx,sy,INDEX,sub,0,0);
      if(ans == 0 && sub >= 2)
	{
	  printf("-1\n");
	}
      else if(ans == 1e9)
	{
	  printf("0\n");
	}
      else 
	{
	  printf("%d\n",ans);
	}    
    }
  return 0;
}
