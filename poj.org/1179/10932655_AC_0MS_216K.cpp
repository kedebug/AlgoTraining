#include <iostream>
#include <cstdio>
#include <memory.h>
using namespace std;

#define MAXN 100
struct Node{
    int mmax;
    int mmin;
}f[MAXN][MAXN];

int func(const int& a,const int& b,const char& o)
{
    if(o=='t')
        return a+b;
    else
        return a*b;
}
int main()
{
    char op[MAXN];
    int arr[MAXN];
    int n,i,j,mmin,mmax,k,h,tmp,st,en,mid1,mid2,mark_pos;
    while(scanf("%d",&n)!=EOF)
    {
        for(i = 0;i < n; ++i)
        {
            getchar();
            op[i] = getchar();
            scanf("%d",&arr[i]);
        }
        for(i = 0;i < n; ++i)
        {
            f[i][i].mmax = arr[i];
               f[i][i].mmin = arr[i];
        }
        for(k = 1;k < n; ++k)
            for(i = 0;i < n; ++i)
            {
                mmin = 1<<30;
                mmax = -mmin;
                en = (i+k)%n;
                for(j = 0;j < k; ++j)
                {
                    mid1 = (i+j)%n;
                    mid2 = (i+j+1)%n;
                    tmp = func(f[i][mid1].mmin,f[mid2][en].mmin,op[mid2]);
                    mmax = mmax>tmp?mmax:tmp;
                    tmp = func(f[i][mid1].mmax,f[mid2][en].mmax,op[mid2]);
                    mmax = mmax>tmp?mmax:tmp;
                    tmp = func(f[i][mid1].mmin,f[mid2][en].mmax,op[mid2]);
                    mmin = mmin<tmp?mmin:tmp;
                    tmp = func(f[i][mid1].mmax,f[mid2][en].mmin,op[mid2]);
                    mmin = mmin<tmp?mmin:tmp;
                }
                f[i][en].mmax = mmax;
                f[i][en].mmin = mmin;
            }
        mmax = -(1<<30);
        for(i = 0;i < n; ++i)
        {
            en = (i+n-1)%n;
            if(mmax<f[i][en].mmax)
            {
                mark_pos = i;
                mmax = f[i][en].mmax;
            }

        }
        printf("%d\n",mmax);
        int flag = 0;
        for(i = 0;i < n; ++i)
        {
            if(f[i][(i+n-1)%n].mmax == mmax)
            {
                if(!flag)
                {
                    flag = 1;
                    printf("%d",i+1);
                }
                else
                    printf(" %d",i+1);
            }
        }
        printf("\n");
    }
    return 0;
}