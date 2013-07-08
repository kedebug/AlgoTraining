#include <cstdio>
 #include <cstring>
 #include <cstdlib>
 #include <iostream>
 #include <map>
 
 #define N 200 
 
 using namespace std;
 
 map<int,int> mp;
 
 struct MATRIX
 {
     int mt[N][N];
 }dg,fb;
 
 int n,m,S,T,cnt;
 
 inline MATRIX operator +(MATRIX a,MATRIX b)
 {
     MATRIX c;
     memset(c.mt,0x3f,sizeof c.mt);
     for(int k=1;k<=cnt;k++)
         for(int i=1;i<=cnt;i++)
             for(int j=1;j<=cnt;j++)
                 if(c.mt[i][j]>a.mt[i][k]+b.mt[k][j])
                     c.mt[i][j]=a.mt[i][k]+b.mt[k][j];
     return c;
 }
 
 void read()
 {
     mp.clear(); cnt=0;
     memset(dg.mt,0x3f,sizeof dg.mt);
     memset(fb.mt,0x3f,sizeof fb.mt);
     for(int i=1,a,b,sa,sb,sd;i<=m;i++)
     {
         scanf("%d%d%d",&sd,&sa,&sb);
         if(!mp[sa]) mp[sa]=++cnt;
         if(!mp[sb]) mp[sb]=++cnt;
         a=mp[sa]; b=mp[sb];
         if(sd<dg.mt[a][b]) dg.mt[b][a]=dg.mt[a][b]=sd;
     }
     for(int i=1;i<=cnt;i++) fb.mt[i][i]=0;    
 }
 
 void go()
 {
     while(n)//倍增 
     {
         if(n&1) fb=fb+dg;
         dg=dg+dg;
         n>>=1;
     }
     printf("%d\n",fb.mt[mp[S]][mp[T]]);
 }
 
 int main()
 {
 
     while(scanf("%d%d%d%d",&n,&m,&S,&T)!=EOF)
     {
         read();
         go();
     }
     return 0;
 }