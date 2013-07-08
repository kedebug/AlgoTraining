#include <iostream>
using namespace std;
int main()
{
	int i,k,n;
	while(scanf("%d", &n), n)
	{
		if(n%6!=2 && n%6!=3)
		{
			printf("2");
			for(i=4; i<=n; i+=2)
				printf(" %d", i);
			for(i=1; i<=n; i+=2)
				printf(" %d", i);
			printf("\n");
			continue;
		}
		k = n/2;
		printf("%d", k);
		if(!(k & 1) && !(n & 1))
		{
			for(i=k+2; i<=n; i+=2)
				printf(" %d", i);
			for(i=2; i<=k-2; i+=2)
				printf(" %d", i);
			for(i=k+3; i<=n-1; i+=2)
				printf(" %d", i);
			for(i=1; i<=k+1; i+=2)
				printf(" %d", i);        
		}
		else if(!(k & 1) && (n & 1))
		{
			for(i=k+2; i<=n-1; i+=2)
				printf(" %d", i);
			for(i=2; i<=k-2; i+=2)
				printf(" %d", i);
			for(i=k+3; i<=n-2; i+=2)
				printf(" %d", i);            
			for(i=1; i<=k+1; i+=2)
				printf(" %d", i);
			printf(" %d", n);        
		}
		else if((k & 1) && !(n & 1))
		{
			for(i=k+2; i<=n-1; i+=2)
				printf(" %d", i);
			for(i=1; i<=k-2; i+=2)
				printf(" %d", i);
			for(i=k+3; i<=n; i+=2)
				printf(" %d", i);
			for(i=2; i<=k+1; i+=2)
				printf(" %d", i);
		}
		else if((k&1) && (n&1))
		{
			for(i=k+2; i<=n-2; i+=2)
				printf(" %d", i);
			for(i=1; i<=k-2; i+=2)
				printf(" %d", i);
			for(i=k+3; i<=n-1; i+=2)
				printf(" %d", i);
			for(i=2; i<=k+1; i+=2)
				printf(" %d", i);
			printf(" %d", n);
		}
		printf("\n");
	}
	return 0;
}
