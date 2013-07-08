#include<stdio.h>
#include<math.h>
#include<string.h>
#include<algorithm>
#include<iostream>
using namespace std;
#define N 1005
#define V 1020005
int U[V],D[V];
int L[V],R[V];
int C[V];
int H[N],S[N];
int mark[V];
int size,n,m,OK[N],flag;
int tnum[V];
void Link(int r,int c)
{
    S[c]++;C[size]=c;
    U[size]=U[c];D[U[c]]=size;
    D[size]=c;U[c]=size;
    if(H[r]==-1) H[r]=L[size]=R[size]=size;
    else
    {
        L[size]=L[H[r]];R[L[H[r]]]=size;
        R[size]=H[r];L[H[r]]=size;
    }
    mark[size]=r;
    size++;
}
void remove(int c)//删除列
{
    int i,j;
    L[R[c]]=L[c];
    R[L[c]]=R[c];
    for(i=D[c];i!=c;i=D[i])
    {
        for(j=R[i];j!=i;j=R[j])
        {
            U[D[j]]=U[j],D[U[j]]=D[j];
            S[C[j]]--;
        }
    }
}
void resume(int c)
{
    int i,j;
    for(i=U[c];i!=c;i=U[i])
    {
        for(j=L[i];j!=i;j=L[j])
        {
            U[D[j]]=j;D[U[j]]=j;
            S[C[j]]++;
        }
    }
    L[R[c]]=c;
    R[L[c]]=c;
}
void Dance(int k)
{
    int i,j,Min,c;
    if(!R[0])
    {
        flag=1;//标记有解
        sort(OK, OK+k);//如果这样写就只能输出一组解     如果要输出所有解的话,除了tnum数组外还要x和y数组记录精确覆盖里面的第i行在数独中的位置,这样就不用sort了.
        for(int i=0; i<k; i++)
            printf("%d",tnum[mark[OK[i]]]);
        printf("\n");
        return;
    }
    for(Min=N,i=R[0];i;i=R[i])
        if(S[i]<Min) Min=S[i],c=i;
    remove(c);//删除该列
    for(i=D[c];i!=c;i=D[i])
    {
        OK[k]=i;
        for(j=R[i];j!=i;j=R[j])
            remove(C[j]);
        Dance(k+1);
        if(flag) return;//只要一组解
        for(j=L[i];j!=i;j=L[j])
            resume(C[j]);
    }
    resume(c);
}
/*
试构造一个矩阵，其中以行表示概然，以列表示约束。
行所表示的概然状态为（r,c,k）即在棋盘r行c列放置数字k。
列所表示的约束分做四种，即改当前方案r行中是否放置数k，c列中是否放置数k，
(r,c)格中是否放置数k以及块b(即所属区域)是否放置数k。
因此行总共有N*N*N=9*9*9=729个，列总共有9*9*4=324个，要求取若干数字摆放的方案(行)，
使每个数字在棋盘的行、列、区域块中(列)只出现一次(1个‘1’)，问题转化为729*324的
矩阵的精确覆盖。特别的，(r,c)格的约束保证了我们最后可行解的一定为N*N。
*/
char str[100];
int mat[N][N];
int main()
{
    while(scanf("%s",str)==1&&strcmp(str,"end")!=0)
    {
        memset(mat,0,sizeof(mat));
        m=9*9*4;//列数
        n=0;//构图花费时间比较多  应该直接构图 不用mat数组  这样会快很多
        for(int i=1,pl=0;i<=9;i++)
        {
            for(int j=1;j<=9;j++)
            {
                int row=i;
                int col=j;
                int kuai=(i-1)/3*3+(j-1)/3+1;
                int pos=(i-1)*9+j;
                if(str[pl++]=='.')//可以放数字
                {
                    for(int k=1;k<=9;k++)
                    {
                        ++n;
                        tnum[n]=k;
                        mat[n][(row-1)*9+k]=1;//行
                        mat[n][81+(col-1)*9+k]=1;//列
                        mat[n][162+(kuai-1)*9+k]=1;//块
                        mat[n][243+pos]=1;//位置
                    }
                }
                else//已经放数字
                {
                    int k=str[pl-1]-'0';
                    ++n;
                    tnum[n]=k;
                    mat[n][(row-1)*9+k]=1;//行
                    mat[n][81+(col-1)*9+k]=1;//列
                    mat[n][162+(kuai-1)*9+k]=1;//块
                    mat[n][243+pos]=1;//位置
                }
            }
        }
        //DLX
        for(int i=0;i<=m;i++)
        {
            S[i]=0;
            D[i]=U[i]=i;
            L[i+1]=i;R[i]=i+1;
        }R[m]=0;
        size=m+1;
        memset(H,-1,sizeof(H));
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                if(mat[i][j]) Link(i,j);
            }
        }
        flag=0;
        Dance(0);
    }
    return 0;
}