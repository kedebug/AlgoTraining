#include <iostream>
using namespace std;

const int MAXN = 1010;
const int inf = 2000000;
struct platform{
    int x1,x2,h;
}p[MAXN];
int dp[MAXN][2];

int cmp(const void *a,const void *b){
    platform *p1 = (platform *)a;
    platform *p2 = (platform *)b;
    return p1->h - p2->h;
}
int main(){
    int t,n,i,j,x,y,MAX;
    scanf("%d",&t);
    while(t--){
        scanf("%d %d %d %d",&n,&x,&y,&MAX);
        for(i=1;i<=n;i++){
            scanf("%d %d %d",&p[i].x1,&p[i].x2,&p[i].h);
            if(p[i].x1>p[i].x2)
                swap(p[i].x1,p[i].x2);
        }
        p[0].x1=x,p[0].x2=x,p[0].h=y;
        p[n+1].x1=-20001,p[n+1].x2=20001,p[n+1].h=0;
        qsort(p,n+2,sizeof(p[0]),cmp);
        for(i=1;i<=n+1;i++){
            for(j=i-1;j>=0;j--)
                if(p[i].x1>=p[j].x1 && p[i].x1<=p[j].x2){
                    if(p[i].h-p[j].h>MAX)
                        dp[i][0]=inf;
                    else if(j==0)
                        dp[i][0]=p[i].h-p[j].h;
                    else
                        dp[i][0]=min(dp[j][0]+p[i].x1-p[j].x1+p[i].h-p[j].h,dp[j][1]+p[j].x2-p[i].x1+p[i].h-p[j].h);
                    break;
                }
            for(j=i-1;j>=0;j--)
                if(p[i].x2>=p[j].x1 && p[i].x2<=p[j].x2){
                    if(p[i].h-p[j].h>MAX)
                        dp[i][1]=inf;
                    else if(j==0)
                        dp[i][1]=p[i].h-p[j].h;
                    else
                        dp[i][1]=min(dp[j][0]+p[i].x2-p[j].x1+p[i].h-p[j].h,dp[j][1]+p[j].x2-p[i].x2+p[i].h-p[j].h);
                    break;
                }
        }
        printf("%d\n",min(dp[n+1][0],dp[n+1][1]));
    }
    return 0;
}