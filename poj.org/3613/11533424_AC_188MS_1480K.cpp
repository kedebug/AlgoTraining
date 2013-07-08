#include <iostream>
 #include <cstdio>
 #include <cstring>
 #include <algorithm>
 
 using namespace std;
 
 #define maxn 205
 
 int n,t,st,en;
 struct Mat
 {  
     int mat[maxn][maxn];  
     void init()
     {
         memset(mat,-1,sizeof(mat));
     }
 };  
 
 int v[1005];//离散化用
 Mat ans,tmp,map;
 int cnt;//顶点个数
 void init()
 {
     int val,s,e;
     memset(v,0,sizeof(v));
     cnt=0;
     ans.init();
     tmp.init();
     map.init();
     for(int i=0;i<maxn;i++)
         ans.mat[i][i]=0;
     for(int i=0;i<t;i++)
     {
         scanf("%d%d%d",&val,&s,&e);
         if(v[s]==0)
         {
             ++cnt;
             v[s]=cnt;
         }
         if(v[e]==0)
         {
             ++cnt;
             v[e]=cnt;
         }
         if(map.mat[v[s]][v[e]]<0 || map.mat[v[s]][v[e]] > val)
             map.mat[v[s]][v[e]]=map.mat[v[e]][v[s]]=val;
     }
 }
 
 void floyd(Mat b,Mat c)
 {
     tmp.init();
     for(int k=1;k<=cnt;k++)
         for(int i=1;i<=cnt;i++)
             for(int j=1;j<=cnt;j++)
             {    
                 if(b.mat[i][k] <0 || c.mat[k][j] <0)//意味着是inf
                     continue;
                 if(tmp.mat[i][j]<0 || tmp.mat[i][j] > b.mat[i][k] + c.mat[k][j]  )
                      tmp.mat[i][j] = b.mat[i][k] + c.mat[k][j];
             }
 }
 
 Mat copy()
 {
     Mat a;
     for(int i=0;i<=cnt;i++)
         for(int j=0;j<=cnt;j++)
             a.mat[i][j]=tmp.mat[i][j];
     return a;
 }
 
 void solve()
 {
     while(n)//虽然这里是n，像是更新了n次。但是下面80行那里第一次调用的时候其实并未更新。只是把map,传递给tmp再转给ans.
     {
         if(n&1)
         {
             floyd(ans,map);
             ans=copy();
         }
         floyd(map,map);
         map=copy();
         n>>=1;
     }
 }
 
 int main()
 {
     while(scanf("%d%d%d%d",&n,&t,&st,&en) != EOF)
     {
         init();
         solve();
         printf("%d\n",ans.mat[v[st]][v[en]]);
     }
     return 0;
 }