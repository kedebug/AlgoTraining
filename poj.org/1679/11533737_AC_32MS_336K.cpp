#include <iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int INF=9999999 ;
const int MAXN=107 ;
struct  Edge
{
      int u,v,w ;
};
Edge  edge[MAXN*MAXN] ;
int father[MAXN] ;
bool k[MAXN*MAXN],mk[MAXN*MAXN] ;
int m ,n;
int  cmp(const void *a,const void *b)
{
         return (*(Edge*)a).w-(*(Edge*)b).w  ;
}
void make_set()
{
       for(int i=1 ;i<=n ;i++)
                father[i]=i ;
}
int  find_set(int x)
{
    return  (father[x]==x) ?  x : father[x]=(find_set(father[x])) ;
}
void union_set(int x,int y)
{
          x=find_set(x),y=find_set(y) ;
          father[x]=y ;
}
int  compara(int x,int y)
{
          return x<y ? x : y ;
}
int kruskal()
{
      int i,j ;
      make_set() ;
      int weight=0 ;
      for( i=1,j=0 ;i<=m&& j<n-1 ;i++)
      {
            if(find_set(edge[i].u)!=find_set(edge[i].v))
            {
                  union_set(edge[i].u ,edge[i].v ) ;
                  weight+=edge[i].w ;
                  k[i]=true ;
                  j++ ;
            }
      }
      return weight ;
}
int Mkruskal()
{
      int i,j ;
      make_set() ;
      int weight=0 ;
      for(i=1,j=0 ;i<=m&& j<n-1 ;i++)
      {
            if(find_set(edge[i].u)!=find_set(edge[i].v) && mk[i])
            {
                  union_set(edge[i].u ,edge[i].v ) ;
                  weight+=edge[i].w ;
                  j++ ;
            }
      }
      if(j>=n-1)
         return weight ;
         else
         return INF ;
}
int main()
{
    int  i, t ;
    cin>>t ;
    while(t--)
    {
           cin>>n>>m ;

      for(i=1 ;i<=m ;i++)
      {
             cin>>edge[i].u>>edge[i].v>>edge[i].w   ;
      }
      for(i=1 ;i<=m ;i++)
      {
                k[i]=false ;
                mk[i]=true ;
      }
      qsort(edge,m,sizeof(*edge),cmp);
      int mst=kruskal()  ;
      int mmst=INF  ;
      for(i=1 ;i<=m ;i++)
       {
           if(k[i])
           {
                   mk[i]=false ;
                   mmst=compara(mmst,Mkruskal()) ;
                   mk[i]=true ;
           }
       }
       if(mmst<=mst)
             cout<<"Not Unique!"<<endl ;
             else
                   cout<<mst<<endl ;
    }
    return 0;
}