#include "stdio.h"
#include "string.h"
#include <queue>
using namespace std;
#define M 15

int a[M][M],n,c;
int movex[]={0,-1,-1,0,1,1};
int movey[]={-1,-1,0,1,1,0};

int score(int x,int y,int w)//(x,y)放置w，得分
{
 int b[M][M],flag;
 int i,j,k,t;
 int px,py,ans=0;
 memset(b,0,sizeof(b));//标记是否被扫描过
 queue<int> q;
 a[x][y]=w;
 for(i=0;i<n;i++)
 {
  for(j=0;j<=i;j++)
  {
   if(a[i][j]==0)//非0的才扫描
    continue;
   if(b[i][j])
    continue;
   flag=0;
   q.push(i),q.push(j);
   b[i][j]=1;
   while(!q.empty())//扫描该区域
   {
    px=q.front();q.pop();
    py=q.front();q.pop();
    for(k=0;k<6;k++)
    {
     if(px+movex[k]<0||px+movex[k]==n)
      continue;
     if(py+movey[k]<0||py+movey[k]>px+movex[k])
      continue;
     if(b[px+movex[k]][py+movey[k]])
      continue;
     if(a[movex[k]+px][py+movey[k]]==0)//有1个0，则不用移走
     {
      flag=1;
      continue;
     }
     if(a[movex[k]+px][py+movey[k]]==a[i][j])
     {
      q.push(px+movex[k]);
      q.push(py+movey[k]);
      b[px+movex[k]][py+movey[k]]=1;
     }
    }
   }
   if(!flag)//需要移走，统计
   {
    t=0;
    q.push(i);
    q.push(j);
    b[i][j]++;
    while(!q.empty())
    {
     px=q.front();q.pop();
     py=q.front();q.pop();
     t++;
     for(k=0;k<6;k++)
     {
      if(px+movex[k]<0||px+movex[k]==n)
       continue;
      if(py+movey[k]<0||py+movey[k]>px+movex[k])
       continue;
      if(b[movex[k]+px][py+movey[k]]==2)
       continue;
      if(a[movex[k]+px][py+movey[k]]==a[i][j])
      {
       q.push(px+movex[k]);
       q.push(py+movey[k]);
       b[movex[k]+px][py+movey[k]]=2;
      }
     }
    }
    if(a[i][j]==w)
     ans-=t;
    else ans+=t;
   }
  }
 }
 a[x][y]=0;
 return ans;
}

int main()
{
 int i,j;
 //freopen("in2.txt","r",stdin);
 while(scanf("%d%d",&n,&c)>0)
 {
  if(n==0&&c==0)
   break;
  for(i=0;i<n;i++)
  {
   for(j=0;j<=i;j++)
   {
    scanf("%d",&a[i][j]);
   }
  }
  int max=-100;
  for(i=0;i<n;i++)
  {
   for(j=0;j<=i;j++)
   {
    if(a[i][j]==0)
    {
     int t=score(i,j,c);
     if(t>max)
      max=t;
    }
   }
  }
  printf("%d\n",max);
 }
 return 0;
}