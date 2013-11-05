#include<iostream>
#include<string>
#include<cstdlib>
#include<algorithm>
using namespace std;
int a[105],p[105],num[105],money[105];
int main()
{
    int i,j,c,n,ncase;
    scanf("%d",&ncase);
    while(ncase--)
    {
        scanf("%d",&c);
        memset(num,0,sizeof(num));
        for(i=1;i<=c;i++)
        {
            scanf("%d%d",&a[i],&p[i]);
            num[i]=num[i-1]+a[i];
        }
        for(i=1;i<=c;i++)
        {
            money[i]=(num[i]+10)*p[i];
            for(j=1;j<i;j++)
                money[i]=min(money[i],(num[i]-num[j]+10)*p[i]+money[j]);
        }
        printf("%d\n",money[c]);
    }
    //system("pause");
    return 0;
}