#include<cstdio>  
#include<cstring>  
#include<string>  
#include<map>  
#include<iostream>  
#include<algorithm>  
using namespace std;  
const int inf = ~0u>>2;  
int n,m;  
char str[16][25];  
int len[20][20];  
int p[110];  
void getp(int m,char b[]){  
    p[1]=0;  
    int i,j=0;  
    for(i=2;i<=m;i++){  
        while(j>0&&b[j+1]!=b[i]) j=p[j];  
        if(b[j+1]==b[i]) j+=1;  
        p[i]=j;  
    }  
}  
int kmp(int n,int m,char a[],char b[]){  
    int i,j=0,Max=0;  
    for(i=1;i<=n;i++){  
        while(j>0&&b[j+1]!=a[i]) j=p[j];  
        if(b[j+1]==a[i]) j+=1;  
        Max=j;  
        if(j==m){  
            j=p[j];  
        }  
    }  
    return Max;  
}  
int dp[1<<15][15];  
int pre[15];  
int le[20];  
int main()  
{  
     
    int t,ca=1,n;  
    scanf("%d",&t);  
    while(t--)  
    {  
        scanf("%d",&n);  
        for(int i=0;i<n;i++)     scanf("%s",str[i]+1),le[i]=strlen(str[i]+1);  
        memset(len,0,sizeof(len));  
        for(int i=0;i<n;i++)  
        {  
            for(int j=i+1;j<n;j++)  
            {   
                memset(p,0,sizeof(p));  
                getp(le[i],str[i]);  
                int tmp=kmp(le[j],le[i],str[j],str[i]);  
                if(tmp>len[i][j])  
                    len[i][j]=tmp;  
                getp(le[j],str[j]);  
                tmp=kmp(le[i],le[j],str[i],str[j]);  
                if(tmp>len[j][i])  
                    len[j][i]=tmp;  
            }  
        }  
        for(int i=0;i<(1<<n);i++)//len[i][j]用i串的前缀去匹配j串的后缀的最大长度  
        {  
            for(int j=0;j<n;j++)  
            {  
                dp[i][j]=inf;  
                if(i&(1<<j))  
                {  
                    if((i^(1<<j)) == 0) dp[i][j]=le[j];  
                    else   
                    {  
                        for(int k=0;k<n;k++)  
                        {  
                            if((i&(1<<k)) && j!=k)  
                            {  
                                dp[i][j]=min(dp[i][j],dp[i^(1<<j)][k]+le[j]-len[j][k]);  
                            }  
                        }  
                    }  
                }  
            }  
        }  
        int ans=inf;  
        for(int i=0;i<n;i++)  
            ans=min(ans,dp[(1<<n)-1][i]);  
        printf("%d\n",ans);  
    }  
    return 0;  
}  