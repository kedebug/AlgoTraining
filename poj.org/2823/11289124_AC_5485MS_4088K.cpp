#include<cstdio>
#include<iostream>
using namespace std;
const int mm=1111111;
int a[mm],q[mm];
int main()
{
    int i,n,m,l,r;
    while(~scanf("%d%d",&n,&m))
    {
        if(m>n)m=n;
        for(i=1;i<=n;++i)
            scanf("%d",&a[i]);
        l=0,r=-1;
        for(i=1;i<=n;++i)
        {
            while(l<=r&&a[q[r]]>a[i])--r;
            q[++r]=i;
            while(i-q[l]>=m)++l;
            if(i>=m)printf("%d%c",a[q[l]],i<n?' ':'\n');
        }
        l=0,r=-1;
        for(i=1;i<=n;++i)
        {
            while(l<=r&&a[q[r]]<a[i])--r;
            q[++r]=i;
            while(i-q[l]>=m)++l;
            if(i>=m)printf("%d%c",a[q[l]],i<n?' ':'\n');
        }
    }
    return 0;
}
