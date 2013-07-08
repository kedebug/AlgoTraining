#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
int sudo[10][10];

struct type
{
       int x,y,count; 
}status[82];  
int num_status=0;

bool check(int i, int j, int t)//judge if it is possible to put digit t at (i,j)
{
     for(int k=1; k<=9; k++)
             if(sudo[i][k]==t)return false;
     for(int k=1; k<=9; k++)
             if(sudo[k][j]==t)return false;
     int x=(i-1)/3*3+1 ,y=(j-1)/3*3+1;
     for(int s=0; s<=2; s++)
     for(int tt=0; tt<=2; tt++)
             if(sudo[x+s][y+tt]==t)return false;
     return true;             
}

int cal(int i, int j)//calculate the the number of  possible status of (i,j) 
{
    int cnt=0;
    for(int p=1; p<=9; p++)
            if(check(i,j,p))cnt++;
            
    return cnt;
}


bool cmp(const type &a, const type &b)
{
     return a.count<b.count;
}

void dfs(int cnt,bool &find)
{
     if(cnt>num_status)return ;
     if(find){ return ;}
     int x=status[cnt].x; 
     int y=status[cnt].y;
     
     if(cnt==num_status)
     {
              for(int p=1; p<=9; p++)
                      if(check(x,y,p))
                      {
                                      sudo[x][y]=p;
                                      for(int i=1; i<=9; i++)
                                      {
                                              for(int j=1; j<=9; j++)
                                                      cout<<sudo[i][j];
                                              cout<<endl;
                                      }
                                      find=true;
                                      return ;
                      }
                      return ;    
     }
     for(int p=1; p<=9; p++)
     {
             if(check(x,y,p))
             {
              sudo[x][y]=p;
              dfs(cnt+1,find);
             }
            sudo[x][y]=0; //刚开始一直错就因为没置0，check函数当当前位置是0的时候才有效。
     }
         
}

 

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
       memset(sudo,0,sizeof sudo); 
       char ch;
       num_status=0;
       for(int i=1; i<=9; i++)
               for(int j=1; j<=9; j++)
               { 
                cin>>ch;
                sudo[i][j]=int(ch-'0');
                }
                
       for(int i=1; i<=9; i++)
       for(int j=1; j<=9; j++)
                  if(sudo[i][j]==0)
                  {
                      num_status++; 
                      status[num_status].x=i; status[num_status].y=j; 
                      status[num_status].count=cal(i,j); 
                  }
       
       sort(status+1,status+1+num_status,cmp);
      // for(int i=1; i<=num_status ;i++)
        //      cout<<' '<<status[i].x<<' '<<status[i].y<<' '<<status[i].count<<endl;

       
       bool find=false;
       dfs(1,find);
       if(num_status==0)
       {
                    for(int i=1; i<=9; i++)
                    {
                              for(int j=1; j<=9; j++)
                                   cout<<sudo[i][j];
                              cout<<endl;
                    }    
       }
    }
    system("pause");
    return 0;
}