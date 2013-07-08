#include <stdio.h>
#include <math.h>
#define MAXN 1010
#define INF 1e50
#define eps 1e-5

struct Point{
	double x,y,z;
} v[MAXN];
int n,pre[MAXN];
double cost[MAXN][MAXN],dist[MAXN][MAXN],map[MAXN][MAXN],d[MAXN],totdist,totcost;
bool visit[MAXN];

double Prim(double rate){
	int i,j,k;
	double mind;
	for (i=0;i<n;++i)
		for (map[i][i]=0,j=i+1;j<n;++j)
			map[j][i] = map[i][j] = cost[i][j] - rate * dist[i][j];

	for (i=0;i<n;++i){
		visit[i] = false;
		d[i] = map[0][i];
		pre[i] = 0;
	}
	visit[0] = true;

	for (i=1;i<n;++i){
		for (mind=INF,j=0;j<n;++j)
			if (!visit[j] && mind>d[j])		mind=d[k=j];
		visit[k]=true;
		for (j=0;j<n;++j)
			if (!visit[j] && d[j]>map[k][j])	d[j]=map[pre[j]=k][j];
	}
	totdist=totcost=0;
	for (i=1;i<n;++i){
		totdist+=dist[pre[i]][i];
		totcost+=cost[pre[i]][i];
	}
	return totcost/totdist;
}

void Solve(){		//迭代搜索
	double res1=0,res2=0;
	while (true){	//res1为前一次迭代的结果,res2为本次迭代的结果
		res2=Prim(res1);
		if (-eps<res2-res1  &&  res2-res1<eps)		break;
		res1 = (res1 + res2) / 2;
	}
	printf("%.3f\n", res2);
}

int main(){
	int i,j;
	while ( scanf("%d", &n)!=EOF && n){
		for (i=0;i<n;++i)
			scanf("%lf %lf %lf", &v[i].x, &v[i].y, &v[i].z);

		for (i=0;i<n;++i)
			for (dist[i][i]=0,j=i+1;j<n;++j){
				dist[i][j] = dist[j][i] = sqrt( (v[i].x-v[j].x)*(v[i].x-v[j].x) + (v[i].y-v[j].y)*(v[i].y-v[j].y) );
				cost[i][j] = cost[j][i] =  v[i].z-v[j].z<0 ? v[j].z-v[i].z : v[i].z-v[j].z;
		}
		Solve();
	}

	return 0;
}