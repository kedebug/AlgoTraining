#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
int n,m,k;//n,m为plates的行和列
int bad[151][11];//存储坏的unit
int dp[2][60000];//使用滚动数组
int stateA[11],stateB[11];//记录当前行与上一行的状态
int fact3[11];//存放3的指数次方的值
void GetFact3()
{
    int i;
    for (i = 1,fact3[0] = 1; i<11; i++)
        fact3[i] = fact3[i-1] * 3;
}
int GetState(int f[])
{
    int temp = 0,i;
    for (i = 1; i <= 10; i++)
        temp += f[i] * fact3[i-1];
    return temp;
}
void BackState(int i,int f[])
{
    int j;
    for (j = 1; j <= 10; j++)//此处不能用memset函数
    {
        f[j] = i % 3;
        i /= 3;
    }
}
void Init()
{
    int i;
    memset(dp[1],-1,sizeof(dp[1]));
    memset(stateA,0,sizeof(stateA));
    for (i = 1; i <= m; i++)
        stateA[i]=bad[1][i]+1;
    dp[1][GetState(stateA)] = 0;//当前状态可用,而且芯片开始的个数为0
}
inline int Max(int a,int b)
{
    return a>b?a:b;
}
void Dfs(int x,int i,int ct,int state)//x为行号，i为搜索当前行状态的起始位置，ct为芯片的个数，state为前状态
{
    dp[x % 2][state] = Max(dp[x % 2][state],dp[(x + 1) % 2][GetState(stateB)]);
    int now;//当前行的状态
    if (i >= m)
        return ;
    //为2*3的芯片
    if (i <= m - 2 && stateA[i] == 0 && stateA[i + 1] == 0 && stateA[i + 2] == 0)
    {
        stateA[i] = stateA[i + 1] = stateA[i + 2] = 2;
        now = GetState(stateA);
        dp[x % 2][now] = Max(dp[x % 2][now],ct+1);
        Dfs(x,i+3,ct+1,now);
        stateA[i] = stateA[i + 1] = stateA[i + 2] = 0;
    }
    //为3*2的芯片
    if (i <= m - 1 && stateA[i] == 0 && stateA[i + 1] == 0 && stateB[i] == 0 && stateB[i + 1] == 0)
    {
        stateA[i] = stateA[i + 1] = 2; 
        now = GetState(stateA);
        dp[x % 2][now] = Max(dp[x % 2][now],ct+1);
        Dfs(x,i+2,ct+1,now);
        stateA[i] = stateA[i + 1] = 0;
    }
    Dfs(x,i+1,ct,state);
}
void Dp()
{
    int i,j;
    for (i = 2; i <= n; i++)
    {
        memset(dp[i % 2],-1,sizeof(dp[i % 2]));
        for (j = 0; j < fact3[m]; j++)
            if (dp[(i + 1) % 2][j] != -1)//确保前一行的状态时可用的
            {
                BackState(j,stateB);//获得前一行状态的3进制
                int k;
                for (k = 1; k <= m; k++)
                    if (bad[i][k] == 1)
                        stateA[k] = 2;
                    else
                    {
                        stateA[k] = stateB[k] - 1; 
                        if (stateA[k] < 0)
                            stateA[k] = 0;
                    }
                    //根据前一行状态搜索当前行的状态
                    Dfs(i,1,dp[(i + 1) % 2][j],GetState(stateA));
            }
    }
}
void Ans()
{
    int ans = 0,i;
    for (i = 0; i < fact3[m]; i++)
        ans=Max(ans,Max(dp[0][i],dp[1][i]));
    cout<<ans<<endl;
}
int main(void)
{
    int d,i;
    GetFact3();
    cin>>d;
    for (i = 0; i < d; i++)
    {
        cin>>n>>m>>k;
        int j,x,y;
        memset(bad,0,sizeof(bad));
        for (j = 0; j < k; j++)
        {
            cin>>x>>y;
            bad[x][y] = 1;
        }
        if (n < 2)
        {
            cout<<0<<endl;
            continue;
        }
        Init();
        Dp();
        Ans();
    }
    // system("pause");
}