#include<iostream>
#include<cstdio>
#include<memory.h>
using namespace std;
const int inf = 0x7ffffff;
const int N = 729;
const int M= 324;
const int head = 0;
int U[N*M+10],D[N*M+10],L[N*M+10],R[N*M+10];   //四个方向 
int C[N*M+10],row[N*M+10];        //列，行 
int S[M+10],O[N+10];         //s为所在列的结点个数，O为结果选取的行 
char s[100];
int su[N+10][M+10];
int ak;
int n,m;
int ans[100];
void remove(int c)
{
    int i,j;
    L[R[c]]=L[c];
    R[L[c]]=R[c];
    for (i=D[c];i!=c;i=D[i])
        for (j=R[i];j!=i;j=R[j])
        {
            U[D[j]]=U[j];
            D[U[j]]=D[j];
            S[C[j]]--;
        }
}
void resume(int c)
{
    int i,j;
    for (i=U[c];i!=c;i=U[i])
        for (j=L[i];j!=i;j=L[j])
        {
            S[C[j]]++;
            U[D[j]]=D[U[j]]=j;
        }
        R[L[c]]=L[R[c]]=c;
}
bool dfs(int k)
{
    int min,c,i,j;
    if (R[head]==head)
    {
        ak=k;
        return 1;

    }
    min=inf;c=0;
    for (i=R[head];i!=head;i=R[i])
        if (S[i]<min)
        {
            min=S[i];
            c=i;
        }
        remove(c);
        for (i=D[c];i!=c;i=D[i])
        {
            for (j=R[i];j!=i;j=R[j])
                remove(C[j]);
            O[k]=row[i];
            if (dfs(k+1))
                return 1;
            for (j=L[i];j!=i;j=L[j])    //一定要反向 
                resume(C[j]);
        }
        resume(c);
        return 0;
}
void build()
{
    int i,j,k;
    int r,c1,c2,c3,c4;
    memset(su,0,sizeof(su));

    for (i=0;i<9;i++)
        for (j=0;j<9;j++)
        {
            if (s[i*9+j]=='.')
                for (k=1;k<=9;k++)        //i+1行，j+1列，放进k 
                {
                    r=(i*9+j)*9+k;        //该位置的数字k 
                    c1=i*9+k;         //第i+1行的数字k 
                    c2=81+j*9+k;        //第j+1列的数字k 
                    c3=162+(i/3*3+j/3)*9+k;      //第i/3*3+j/3+1个格子的数字k 
                    c4=243+i*9+j+1;        //该数字在数独中的位置 
                    su[r][c1]=su[r][c2]=su[r][c3]=su[r][c4]=1;
                }
            else
            {
                k=s[i*9+j]-'0';
                r=(i*9+j)*9+k;       
                c1=i*9+k;        
                c2=81+j*9+k;       
                c3=162+(i/3*3+j/3)*9+k;      
                c4=243+i*9+j+1;       
                su[r][c1]=su[r][c2]=su[r][c3]=su[r][c4]=1;
            }
        }
}
int main()
{
    int i,j,k,cnt,rowh;
    while (gets(s))
    {
        if (s[0]=='e')
            break;
        memset(ans,0,sizeof(ans));
        build();          //构建01矩阵  
        //建立DLX 
        memset(S,0,sizeof(S));
        for (i=1;i<=M;i++)
            R[i-1]=L[i+1]=U[i]=D[i]=i;
        R[head]=1;R[M]=0;
        cnt=M+1;
        for (i=1;i<=N;i++)    
        {
            rowh=-1;
            for (j=1;j<=M;j++)
            {
                if (su[i][j]==1)
                {
                    C[cnt]=j;
                    U[cnt]=U[j];
                    D[U[j]]=cnt;
                    D[cnt]=j;
                    U[j]=cnt;
                    row[cnt]=i;
                    S[j]++;
                    if (rowh==-1)
                    {
                        R[cnt]=L[cnt]=cnt;
                        rowh=cnt;
                    }
                    else
                    {
                        L[cnt]=L[rowh];
                        R[L[cnt]]=cnt;
                        R[cnt]=rowh;
                        L[rowh]=cnt;
                    }
                    cnt++;
                }
            }
        }
        dfs(0);
        for (i=0;i<ak;i++)
            ans[(O[i]-1)/9]=(O[i]-1)%9+1;
        for (i=0;i<81;i++)
            printf("%d",ans[i]);
        puts("");
    }
}