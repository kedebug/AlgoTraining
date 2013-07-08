#include<iostream>
#include<cstdlib>
#include<string>
#include<algorithm>
using namespace std;
__int64 q[1000000];
__int64 n;
void BFS()
{
     int front,rear;
     __int64 u,ans;
     front=rear=0;
     q[rear++]=1;
     while(front<rear)
     {
          u=q[front++];
          ans=10*u;
          if(ans%n==0)
          {
             printf("%I64d\n",ans);
             return;
          }
          q[rear++]=ans;
          ans++;                                                                                         //这里加1后该数字也还是只有0和1组成
          if(ans%n==0)
          {
             printf("%I64d\n",ans);
             return;
          }
          q[rear++]=ans;
     }
}
int main()
{
    while(scanf("%I64d",&n)!=EOF)
    {
         if(n==0)
            break;
         if(n==1)
         {
            printf("1\n");
            continue;
         }
         BFS();
    }

    return 0;
}