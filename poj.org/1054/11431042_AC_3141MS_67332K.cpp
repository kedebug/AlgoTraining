#include <iostream>
#include <algorithm>
using namespace std;

#define  N  5000+3
#define  inf 0x3f3f3f3f
#define  prim  10079
struct Pn//点
{
 int x,y;
 int next;//指向下一个点号
 bool operator < (const Pn &u)
 {
  if(y == u.y)
   return x < u.x;
  return y < u.y;
 }
};
int dp[N][N];//dp[i][j]存放j延伸到i时的点个数
int hash[prim];//hash链表
int r,c,n;
Pn pn[N];

bool Inner(int x,int y)//是否在范围内
{
 return (x>=1 && x<=r && y >= 1 && y <= c);
}
int HashXy(int x,int y)//hash函数，这里完全是要这个函数优劣了，想想还有没有其他的hash方法
{
 return (x+y + x*y)% prim;
}
int GetNo(int x,int y)//查找该坐标值的点号
{
 int ha = HashXy(x,y);
 int j = hash[ha];

 while(j != -1)
 {
  if(x == pn[j].x && y == pn[j].y)
   return j;
  j = pn[j].next;
 }

 return -1;
}
int main()
{

 scanf("%d %d",&r,&c);

 scanf("%d",&n);

 memset(hash,-1,sizeof(hash));
 int i,j;
 for(i = 0;i <n;i++)
  scanf("%d %d",&pn[i].x,&pn[i].y);

 sort(pn,pn+n);//这里用到排序主要起到以免重复的dp

 int ha;
 for(i = 0; i < n ;i++)//对每个点存入hash表
 {
  ha = HashXy(pn[i].x,pn[i].y);

  pn[i].next = hash[ha];
  hash[ha] = i;
 }

 int x0,y0,x1,y1,Maxp = 2;
 for(i = 1; i <n ;i++)//枚举新的延伸点
 {
  for(j =0 ; j <i ; j++)//dp以前的点
  {
   x0 = 2*pn[j].x-pn[i].x;
   y0 = 2*pn[j].y-pn[i].y;

   if(Inner(x0,y0))//如果这条直线相对于以前点的起点在范围内
   {
    ha = GetNo(x0,y0);//找点号
    if(ha !=-1)
     dp[i][j] = dp[j][ha] +1;//dp新的延伸点
    else
     dp[i][j] = -inf;//如果在范围内的不存在，说明这条直线永远都无法满足要求
   }
   else dp[i][j] = 2;

   x1 = 2*pn[i].x-pn[j].x;
   y1 = 2*pn[i].y-pn[j].y;

   if(!Inner(x1,y1))//如果新点的延伸点在范围外，则这条直线终止
    Maxp = max(Maxp , dp[i][j]);

  }
 }

 if(Maxp > 2)//这里要注意了，满足的直线点最少为3个
  cout<<Maxp;
 else cout<<"0";
 return 0;
}