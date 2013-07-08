#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
#define	maxn 1005
using namespace std; 

int		n,m,data[maxn],t[maxn],cnt;
bool	in_que[maxn];
double	d[maxn]; 
struct	Edge{
	int	to,w; 
	Edge *next; 
}*mat[maxn], edges[maxn*5]; 

void	link(int x ,int to ,int w )
{
	edges[cnt].to = to; 
	edges[cnt].w  = w; 
	edges[cnt].next = mat[x]; 
	mat[x] = &edges[cnt++];
}

bool	pan(double mid )
{
	queue<int> que; 
	while( !que.empty() ) que.pop();
	memset( d , 0 , sizeof(d) );
	memset(in_que,true,sizeof(in_que) );
	memset( t , 0 , sizeof(t) ); 
	for (int i = 1; i<=n; i++) que.push(i); 
	while ( !que.empty() )
	{
		int i = que.front(); 
		in_que[i] = false; 
		que.pop();
		for ( Edge *p = mat[i]; p ; p = p->next )
		{
			int to = p->to; 
			double w = data[to]-mid*p->w; 
			if ( w+d[i] > d[to] )
			{
				t[to]++; 
				if ( t[to] >= n ) return true; 
				d[to] = w+d[i]; 
				if ( !in_que[to] ) {
					in_que[to] = true; 
					que.push(to); 
				}

			}
		}
	}
	return false; 
	
}

int		main()
{
	int x,y,w;
	scanf("%d%d",&n,&m );
	for (int i = 1; i<=n; i++) scanf("%d", &data[i] );
	for (int i = 0; i<m ; i++)
	{
		scanf("%d%d%d", &x, &y ,&w ); 
		link( x ,y , w );
	}
	double	g = 0 , h = 10000.0, ans = -1;
	while ( fabs(g-h)>1e-4 ) 
	{
		double	mid = (g+h)/2;
		if ( pan(mid) )
		{
			ans = mid; 
			g = mid; 
		}
		else h = mid; 
	}
	if ( ans < 0 ) printf("0\n");
	else printf("%.2f\n" ,ans );
	return 0; 
}