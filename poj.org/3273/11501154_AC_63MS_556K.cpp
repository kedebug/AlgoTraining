#include<iostream>
#include<cstdio>
using namespace std;

int m , n , a[100001];

int bsearch(int low , int high)
{
	int i , mid , group , sum;
	while(low <= high)
	{
		mid = (low + high)>>1;
		sum = 0 ,  group = 1;
		for(i = 0 ; i < n ; ++i)
		{
			if(sum + a[i] <= mid)
				sum += a[i];
			else
			{
				group++;
				sum = a[i];
			}
		}
		if(group <= m)
			high = mid - 1 ;
		else if(group > m)
			low = mid + 1;
	}
	return low;
}

int main(void)
{
	int i , max , sum;
	while(scanf("%d %d",&n,&m)!=EOF)
	{
		max = 0x80000000 , sum = 0;
		for(i = 0 ; i < n ; ++i)
		{
			scanf("%d",&a[i]);
			sum += a[i];
			if(a[i] > max)
				max = a[i];
		}
		printf("%d\n",bsearch(max, sum));
	}
	return 0;
}