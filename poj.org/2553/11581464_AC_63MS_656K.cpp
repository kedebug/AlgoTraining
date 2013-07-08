#include<iostream>  
#include<stack>  
#include<math.h>  
#define MAXN 5001  
using namespace std;  
struct pp  
{    
    int x,y,next;     
}line[MAXN*5];  
int n,m,link[MAXN],i,p,low[MAXN],dfn[MAXN],tp[MAXN],numtp,sum[MAXN];  
bool instack[MAXN],used[MAXN];  
stack<int> mystack;  
void tarjan(int h)  
{  
   int k;  
   instack[h]=true;  
   mystack.push(h);  
   low[h]=dfn[h]=++p;  
   k=link[h];  
   while (k)  
   {  
      if (!dfn[line[k].y])  
      {  
            tarjan(line[k].y);  
            low[h]=min(low[h],low[line[k].y]);       
      }else  
      if (instack[line[k].y])  
      {  
            low[h]=min(low[h],dfn[line[k].y]);             
      }  
      k=line[k].next;     
   }  
   k=h;  
   if (low[k]==dfn[k])  
   {  
        numtp++;                
        do   
        {  
             k=mystack.top();  
             tp[k]=numtp;  
             mystack.pop();  
             instack[k]=false;           
        }while ( low[k]!=dfn[k]);                
   }  
   return;   
}   
void getanswer()  
{  
    int i;  
    memset(instack,false,sizeof(instack));  
    while (!mystack.empty()) mystack.pop();  
    memset(tp,0,sizeof(tp));  
    memset(dfn,0,sizeof(dfn));  
    p=0; numtp=0;  
    for (i=1;i<=n;i++)   
     if (!dfn[i])   
       tarjan(i);   
    for (i=1;i<=n;i++)  
     if (!tp[i])  
     {  
         printf("\n");  
         return;             
     }     
    memset(link,0,sizeof(link));  
    memset(sum,0,sizeof(sum));   
    for (i=1;i<=m;i++)  
    if (tp[line[i].x]!=tp[line[i].y])  
    {  
        p++;  
        sum[tp[line[i].x]]++;  
    }     
    for (i=1;i<=n;i++)  
     if (!sum[tp[i]])   
       printf("%d ",i);    
    printf("\n");  
    return;  
}  
int main()  
{   
    while (~scanf("%d%",&n))  
    {  
          if (!n) break;  
          scanf("%d",&m);  
          memset(link,0,sizeof(link));  
          memset(line,0,sizeof(line));  
          for (i=1;i<=m;i++)  
          {  
              scanf("%d%d",&line[i].x,&line[i].y);  
              line[i].next=link[line[i].x];  
              link[line[i].x]=i;  
          }  
          getanswer();  
    }  
    return 0;     
}  