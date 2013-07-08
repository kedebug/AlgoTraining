
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
const int maxn = 20010;
int cover[maxn<<2],Max[maxn<<2];
struct Point{
    double x,y;
    int c;
    bool operator < (const Point &cmp)const{
        return y<cmp.y;
    }
}p[maxn];
int ans;
double x[maxn];
inline int max(int a,int b)
{
    return a>b?a:b;
}

void pushdown(int rt)
{
    if(cover[rt])
    {
        cover[rt<<1]+=cover[rt];
        cover[rt<<1|1]+=cover[rt];
        Max[rt<<1]+=cover[rt];
        Max[rt<<1|1]+=cover[rt];
        cover[rt]=0;
    }
}
void pushup(int rt)
{
    Max[rt]=max(Max[rt<<1],Max[rt<<1|1]);
}
void update(int L,int R,int c,int l,int r,int rt)
{
    if(L<=l&&r<=R){
        cover[rt]+=c;
        Max[rt]+=c;
        return ;
    }
    pushdown(rt);
    int m=(l+r)>>1;
    if(L<=m) update(L,R,c,lson);
    if(R>m) update(L,R,c,rson);
    pushup(rt);
}
int main(){
    int n,i,j,k,c;
    double W,H;
    double a,b;
    while(scanf("%d%lf%lf",&n,&W,&H)!=EOF){
        int tot=0;
        ans=0;
        memset(cover,0,sizeof(cover));
        memset(Max,0,sizeof(Max));
        for(i=0;i<n;i++){
            scanf("%lf%lf%d",&p[i].x,&p[i].y,&p[i].c);
            x[tot++]=p[i].x;
            x[tot++]=p[i].x+W;
        }
        sort(p,p+n);
        sort(x,x+tot);
        k=unique(x,x+tot)-x;

        for(i=0,j=0;i<n;i++)
        {
            int left=lower_bound(x,x+k,p[i].x)-x;
            int right=lower_bound(x,x+k,p[i].x+W)-x-1;

            update(left,right,p[i].c,0,k-1,1);

            while(j <= i && p[i].y-p[j].y >= H) 
            {
                left=lower_bound(x,x+k,p[j].x)-x;
                right=lower_bound(x,x+k,p[j].x+W)-x-1;
                update(left,right,-p[j].c,0,k-1,1);
                j++;
            }
            if(Max[1]>ans) ans=Max[1];
        }
        printf("%d\n",ans);
    }
    return 0;
}