#include<stdio.h>  
#include<string.h>  
#define max(a,b) a>b?a:b  
int dp[110][101];  
char s[110];  
int main()  
{  
    char s[110];  
    int i,j,k;  
    while(scanf("%s",s)!=EOF)  
    {  
        int ans=0;  
        if(strcmp(s,"end")==0) break;  
        int len=strlen(s);  
        memset(dp,0,sizeof(dp));  
        for(k=0;k<len;k++)  
        {  
            for(i=0,j=k;j<len;i++,j++)  
            {  
                 if(s[i]=='('&&s[j]==')'||s[i]=='['&&s[j]==']')  
                  dp[i][j]=max(dp[i][j],dp[i+1][j-1]+2);  
                for(int t=i;t<j;t++)  
                  dp[i][j]=max(dp[i][j],dp[i][t]+dp[t+1][j]);     
            }  
        }  
      printf("%d\n",dp[0][len-1]);  
    }  
    return 0;   
} 