
#include<stdio.h>
#include<string.h>

const int N = 22;
int sticks[N];
bool visited[N];
int part;
int n;
//从start根木棒出发，在已经凑齐pnum条边，
//第pnum+1条边已有pre长度的情况下，搜索是否存在满足答案的解
bool search(int start,int pnum,int pre)
{
 if(pnum==3&&pre==part)
  return true;
 if(pre==part)
 {
  pnum++;
  pre=0;
  start = 0;
 }
 
 int i;
 for(i=start;i<n;i++)
 {
  if(visited[i]==false)
  {
   visited[i]=true;
   if(search(i+1,pnum,pre+sticks[i]))
    return true;
   visited[i]=false;
  }
 }
 return false;
}
int main()
{
 int T;
 scanf("%d",&T);
 while(T--)
 {
  scanf("%d",&n);
  int i;
  int sum = 0;
  for(i=0;i<n;i++)
  {
   scanf("%d",&sticks[i]);
      sum+=sticks[i];
  }
  
  memset(visited,false,sizeof(visited));
  part = sum/4;
        if(sum%4==0&&search(0,0,0))
   printf("yes\n");
  else
   printf("no\n");

 }
 return 0;
}