#include<iostream>
using namespace std;
int a[100][100];
int m[100];
int ans[100];
int p[1000000];
int sum,mm,an;
int MAX;
int t,len;
void Backtrack(int i,int l);
int main()
{
	int i,j;
	char num[100];
	while(cin>>t>>num)
	{
		memset(a,-1,sizeof(a));
		len=strlen(num);
		if(t==0&&len==1&&num[0]=='0')
			break;
		for(i=0;i<len;i++)
		{
			a[i][i]=num[i]-48;
			for(j=i+1;j<len;j++)
				a[i][j]=a[i][j-1]*10+num[j]-48;
		}
		Backtrack(0,len);
		if(MAX==0)
			cout<<"error"<<endl;
		else if(p[MAX]>=1)
			cout<<"rejected"<<endl;
		else
		{
			cout<<MAX;
			for(i=0;i<an;i++)
				cout<<' '<<ans[i];
			cout<<endl;
		}
		p[MAX]=0;
		mm=0;
		sum=0;
		MAX=0;
	}
	return 0;
}
void Backtrack(int i,int l)
{
	int j;
	if(l==0)
	{
		if(sum==MAX)
			p[MAX]++;
		if(sum>MAX)
		{
			p[MAX]=0;
			an=mm;
			memcpy(ans,m,sizeof(int)*mm);
			MAX=sum;
		}
		return;
	}
	for(j=i;j<l+i;j++)
	{
		if(sum+a[i][j]<=t)
		{
			m[mm++]=a[i][j];
			sum+=a[i][j];
			Backtrack(1+j,l-1-(j-i));
			sum-=a[i][j];
			mm--;
		}
	}
}