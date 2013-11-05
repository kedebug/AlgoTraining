
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 1010;
const double INFS = 1e15;
const double eps = 1e-5;

double x[MAXN], y[MAXN], z[MAXN];
double dist[MAXN][MAXN], cost[MAXN][MAXN], map[MAXN][MAXN], d[MAXN];
int p[MAXN], n;
bool vis[MAXN];

double prim(double ratio) {
    for (int i = 1; i <= n; i++) {
        map[i][i] = 0.0;
        for (int j = i+1; j <= n; j++)
            map[i][j] = map[j][i] = cost[i][j] - ratio*dist[i][j];
    }
    for (int i = 1; i <= n; i++)
        d[i] = map[1][i], vis[i] = false, p[i] = 1;
    vis[1] = true;
    for (int k = 1, j; k < n; k++) {
        double mind = INFS;
        for (int i = 2; i <= n; i++) 
            if (!vis[i] && mind > d[i])
                mind = d[i], j = i;
        vis[j] = true;
        for (int i = 2; i <= n; i++) 
            if (!vis[i] && d[i] > map[j][i])
                d[i] = map[j][i], p[i] = j;
    }
    double d1 = 0, c1 = 0;
    for (int i = 2; i <= n; i++) {
        d1 += dist[i][p[i]];
        c1 += cost[i][p[i]];
    }
    return c1 / d1;
}

int main() {
    while (scanf("%d", &n) && n) {
        for (int i = 1; i <= n; i++)
            scanf("%lf%lf%lf", &x[i], &y[i], &z[i]);
        for (int i = 1; i <= n; i++) {
            dist[i][i] = cost[i][i] = 0.0;
            for (int j = i+1; j <= n; j++) {
                dist[i][j] = dist[j][i] = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
                cost[i][j] = cost[j][i] = fabs(z[i] - z[j]);
            }
        }
        double r1 = 0.0, r2 = 0.0;
        while (true) {
            r2 = prim(r1);
            if (fabs(r1 - r2) < eps)
                break;
            r1 = r2;
        }
        printf("%.3lf\n", r1);
    }
    return 0;
}