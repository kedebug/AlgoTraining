#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;
int n;
int map[10][10];
bool row[10][10];  //记录每行的数字是否可行
bool col[10][10];  //记录没列的数字是否可行
bool grid[10][10]; //记录每个九宫格的数字是否可行

void getmap()
{
    char s[10];
    for(int i=0 ;i<9 ;i++)
    {
        getchar();
        scanf("%s",s);
        for(int j=0; j<9; j++)
        {
           map[i][j]=s[j]-'0';
           if(map[i][j]!=0)
           {
               int num=map[i][j];
               int k=3*(i/3)+j/3;  // 这个公式很关键。这是求每个点对应的九宫格
               row[i][num]=true;
               col[j][num]=true;
               grid[k][num]=true;
           }
        }
    }
}

bool dfs(int i,int j)
{
    bool flag=false;
    if(i==9) return true;
    if(map[i][j])
    {
        if(j==8)
        {
            flag=dfs(i+1,0);
        }
        else
        {
            flag=dfs(i,j+1);
        }
        if(flag)   //在这回溯，但不改变map的值，只起到一个传递的作用
            return true;
        else
            return false;
    }
    else
    {
        int k=3*(i/3)+j/3;
        for(int x=1; x<=9; x++)
        {
          if(!row[i][x] && !col[j][x] && !grid[k][x])
          {
              map[i][j]=x;
              row[i][x]=true;
              col[j][x]=true;
              grid[k][x]=true;
              if(j==8)
              {
                  flag=dfs(i+1,0);
              }
              else
              {
                  flag=dfs(i,j+1);
              }

             if(!flag)    //这也是一个回溯
             {
               map[i][j]=0;
               row[i][x]=false;
               col[j][x]=false;
               grid[k][x]=false;
             }
             else
             {
                 return true;
             }
          }//if
        }//for
    }
    return false;
}

void output()
{
    for(int i=0; i<9; i++)
    {
       for(int j=0; j<9; j++)
       {
           printf("%d",map[i][j]);
       }
           printf("\n");
    }
}

int main()
{
    //freopen("acm.txt","r",stdin);
    scanf("%d",&n);
    while(n--)
    {
        memset(row,false,sizeof(row));
        memset(col,false,sizeof(col));
        memset(grid,false,sizeof(grid));
        getmap();
        dfs(0,0);
        output();
    }
    return 0;
}