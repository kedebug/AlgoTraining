#include <cstdio>  
#include <cstdlib>  
#include <string>  
#include <climits>  
#include <iostream>     
#include <vector>  
#include <set>  
#include <cmath>  
#include <cctype>  
#include <algorithm>  
#include <sstream>  
#include <map>  
#include <cstring>  
#include <queue>  
using namespace std;  
const int mod = 100000;  
const int M = 100;  
const int CD = 4;  
int fail[M];  
int Q[M];  
int ch[M][CD];  
int ID[128];  
int val[M];  
int sz;  
void Init(){  
    fail[0]=0;  
    memset(ch[0],0,sizeof(ch[0]));  
    sz=1;  
    ID['A']=0;ID['T']=1;ID['G']=2;ID['C']=3;  
}  
void Insert(char *s){  
    int p=0;  
    for(;*s;s++){  
        int c=ID[*s];  
        if(!ch[p][c]){  
            memset(ch[sz],0,sizeof(ch[sz]));  
            val[sz]=0;  
            ch[p][c]=sz++;  
        }  
        p=ch[p][c];  
    }  
    val[p]=1;  
}  
void Construct(){  
    int  *s=Q,*e=Q;  
    for(int i=0;i<CD;i++){  
        if(ch[0][i]){  
            fail[ch[0][i]] = 0;  
            *e++ = ch[0][i];  
        }  
    }  
    while(s!=e){  
        int u = *s++;  
        for(int i=0;i<CD;i++){  
            int &v = ch[u][i];  
            if(v){  
                *e++ = v;  
                fail[v]=ch[fail[u]][i];  
                val[v]|=val[fail[v]];  
            } else  {  
                v=ch[fail[u]][i];  
            }  
        }  
    }  
}  
long long dp[100][100];  
const int MAX = 100;  
int n;  
struct  Mat {  
    int mat[MAX][MAX];  
    Mat(){  
        memset(mat,0,sizeof(mat));  
    }  
    void init(){  
        for(int i=0;i<n;i++)  
            for(int j=0;j<n;j++)  
                mat[i][j]= i==j;  
    }  
    void print(){  
        printf("****************\n");  
        for(int i=0;i<n;i++)   
            for(int j=0;j<n;j++)  
                printf(j==n-1?"%d\n":"%d ",mat[i][j]);  
        printf("fuckfuckfuckfuckfuck\n");  
    }  
    friend Mat operator *(Mat a,Mat b);  
    friend Mat operator +(Mat a,Mat b);  
    friend Mat operator ^(Mat a,int k);  
}E;  
Mat operator +(Mat a,Mat b)  
{  
    Mat c;  
    for(int i=0;i<n;i++)  
        for(int j=0;j<n;j++)  
        {  
            c.mat[i][j]=a.mat[i][j]+b.mat[i][j];  
            if(c.mat[i][j]>=mod) c.mat[i][j]-=mod;  
        }  
  
        return c;  
}  
Mat operator *(Mat a,Mat b)  
{  
    Mat ans;  
    for(int i=0;i<n;i++)  
        for(int j=0;j<n;j++)  
        {  
            long long tmp=0;  
            for(int k=0;k<n;k++)  
            {  
                tmp+=(long long)a.mat[i][k]*b.mat[k][j];  
            }  
            ans.mat[i][j]=tmp%mod;  
        }  
  
        return ans;  
}  
Mat operator ^(Mat a,int k)  
{  
    Mat ans=E;  
    while(k){  
        if(k&1) ans=ans*a;  
        a=a*a,k>>=1;  
    }  
    return ans;  
}  
int main() {  
    char s[15];  
    int k,m;  
    while(scanf("%d%d",&m,&k)!=EOF) {  
        Init();  
        for(int i=0;i<m;i++)  {  
            scanf("%s",s);  
            Insert(s);  
        }  
        Construct();  
        n=sz;  
        Mat ans;  
        for(int i=0;i<sz;i++)  
        {  
            if(val[i])  
                continue;  
            for(int j=0;j<4;j++)  
            {  
                if(val[ch[i][j]])  
                    continue;  
                ans.mat[i][ch[i][j]]++;  
            }  
        }  
        E.init();  
        ans=ans^k;  
        int ret=0;  
        for(int i=0;i<n;i++)  
        {  
            ret+=ans.mat[0][i];  
            if(ret>=mod) ret-=mod;  
        }  
        printf("%d\n",ret);  
    }  
    return 0;  
}