#include<cstdio>  
#include<set>  
using namespace std;  
const int mm=111111;  
int a[mm],q[mm];  
long long f[mm],sum,tmp,m;  
multiset<int> sbt;  
int i,l,r,p,n;  
int main()  
{  
    scanf("%d%I64d",&n,&m);  
    sbt.clear();  
    sum=l=0,f[n]=r=-1;  
    for(p=i=1;i<=n;++i)  
    {  
        scanf("%d",&a[i]);  
        sum+=a[i];  
        while(sum>m)sum-=a[p++];  
        if(p>i)break;  
        while(l<=r&&a[i]>=a[q[r]])  
        {  
            if(l<r)sbt.erase(f[q[r-1]]+a[q[r]]);  
            --r;  
        }  
        q[++r]=i;  
        if(l<r)sbt.insert(f[q[r-1]]+a[q[r]]);  
        while(q[l]<p)  
        {  
            if(l<r)sbt.erase(f[q[l]]+a[q[l+1]]);  
            ++l;  
        }  
        f[i]=f[p-1]+a[q[l]];  
        tmp=*sbt.begin();  
        if(l<r&&f[i]>tmp)f[i]=tmp;  
    }  
    printf("%I64d\n",f[n]);  
    return 0;  
}  