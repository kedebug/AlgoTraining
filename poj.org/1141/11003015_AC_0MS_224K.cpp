#include <iostream>
using namespace std;

const int MAXN = 110;
char str[MAXN];
int dp[MAXN][MAXN],path[MAXN][MAXN];

void output(int i,int j){
    if(i>j) return;
    if(i==j){
        if(str[i]=='[' || str[i]==']') printf("[]");
        else printf("()");
    }
    else if(path[i][j]==-1){
        printf("%c",str[i]);
        output(i+1,j-1);
        printf("%c",str[j]);
    }
    else{
        output(i,path[i][j]);
        output(path[i][j]+1,j);
    }
}
int main(){
    int i,j,k,r,n;
    while(gets(str)){
        n=strlen(str);
        if(n==0){
            printf("\n");
            continue;
        }
        memset(dp,0,sizeof(dp));
        for(i=0;i<n;i++) dp[i][i]=1;
        for(r=1;r<n;r++)
            for(i=0;i<n-r;i++){
                j=i+r;
                dp[i][j]=INT_MAX;
                if((str[i]=='(' && str[j]==')')||(str[i]=='[' && str[j]==']'))
                    if(dp[i][j]>dp[i+1][j-1])
                        dp[i][j]=dp[i+1][j-1],path[i][j]=-1;
                for(k=i;k<j;k++)
                    if(dp[i][j]>dp[i][k]+dp[k+1][j])
                        dp[i][j]=dp[i][k]+dp[k+1][j],path[i][j]=k;
            }
        output(0,n-1);
        printf("\n");
    }
    return 0;
}