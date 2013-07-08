
#include<stdio.h>
#include<string.h>
#define maxn 300000
int a[maxn],c[maxn],p[maxn];//值为i的数有i个
int find(int x){return x==p[x] ? x : p[x]=find(p[x]);}
int lowbit(int x){
    return x&-x;
}
void update(int x,int d){
    for(;x<=maxn;x+=lowbit(x))
        c[x]+=d;
}//因为是从左往右手动求和了，所以也不需要sum()操作了
int find_kth(int k)//太神奇了(大概是以前没有完全领会)，log(n)复杂度
{
    int ans = 0, cnt = 0, i;
    for (i = 20; i >= 0; i--)//利用二进制的思想，把答案用一个二进制数来表示
    {
        ans += (1 << i);
        if (ans >= maxn|| cnt + c[ans] >= k)
            //这里大于等于k的原因是可能大小为ans的数不在c[ans]的控制范围之内，所以这里求的是 < k
            ans -= (1 << i);
        else
            cnt += c[ans];//cnt用来累加比当前ans小的总组数
    }//求出的ans是累加和（即小于等于ans的数的个数）小于k的情况下ans的最大值，所以ans+1就是第k大的数
    return ans + 1;
}
/*
因为要求第k小的数，所以要从左往右加过去，
上述过程其实就是把树状数组的求和操作逆向，从左往右求和，
边求和边判断控制范围内比当前值要小的数是否超过或等于k,如果是则跳回兄弟节点(ans-=(1<<i))
如8+4=12，假如12不满足要求，则重新变回8，下一次就加2,8+2=10，即跳到10控制的位置
上述累加过程不会重复计算，因为
比如15=8+4+2+1，数字依次为8  12  14  15，每次累加后的值都与前面的值无关，i小于其二进制末尾0的个数
即c[8] 、c[12] 、c[14]、 c[15]相加的话不会重复计算，再如11=8+2+1;数字依次为8 10 11，c[8],c[10],c[11]
各自控制着自己的范围，不会重复累加，所以就可以用cnt来累加前面的结果，最后cnt+c[ans]就表示了值<=ans的个数
简言之：上述的各个数字两两间控制的范围不会相交
*/
int main()
{
    int i,n,m,q,x,y,k,l,r;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++) p[i]=i;
    for(i=1;i<=n;i++) a[i]=1;
    update(1,n);//初始状态值为1的数有n个
    int num=n;
    for(i=1;i<=m;i++)
    {
        scanf("%d",&q);
        if(q==0)
        {
            scanf("%d%d",&x,&y);
            x=find(x);
            y=find(y);
            if(x==y) continue;
            update(a[x],-1);
            update(a[y],-1);
            update(a[x]+a[y],1);
            p[y]=x;
            a[x]+=a[y];
            num--;//合并集合
        }
        else 
        {
            scanf("%d",&k);
            k=num-k+1;//转换为找第k小的数
            printf("%d\n",find_kth(k));
        }
    }
    return 0;
}