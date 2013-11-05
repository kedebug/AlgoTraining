#include <iostream>  
#include <string.h>  
#include <cstdio>  
using namespace std;  
  
#define CLR(arr,val) memset(arr,val,sizeof(val))  
const int N =110;  
int num[N][N],dp[N][N];  
int max(int a,int b){  
    return a>b?a:b;  
}  
int main(){  
    //freopen("1.txt","r",stdin);  
    int n;  
    while(scanf("%d",&n) != EOF){  
        CLR(num,0);  
        for(int i = 1;i <= n;++i){  
          for(int j = 1;j <= i;++j)  
              scanf("%d",&num[i][j]);  
        }  
        CLR(dp,0);  
        dp[1][1] = num[1][1];  
        for(int i = 1;i <= n;++i){  
            for(int j = 1;j <= i;++j){  
              dp[i][j] = max(dp[i-1][j],dp[i-1][j-1]) + num[i][j];  
            }  
        }  
        int mmax = 0;  
        for(int i = 1;i <= n;++i)  
            if(mmax < dp[n][i])  
                mmax = dp[n][i];  
        printf("%d\n",mmax);  
    }  
    return 0;  
}  