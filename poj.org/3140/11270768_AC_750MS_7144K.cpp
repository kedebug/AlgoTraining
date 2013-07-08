#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include <cctype>
#include <map>
#include <iomanip>
                   
using namespace std;
                   
#define eps 1e-8
#define pi acos(-1.0)
#define inf 1<<30
#define linf 1LL<<60
#define pb push_back
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lowbit(x) (x & (-x))
#define ll long long

int n,m;
ll v[100100],dp[100100],summ,ans;
vector<int> way[100100];

ll ABS(ll a){
    if (a>0) return a;
    else return -a;
}

void solve_dfs(int u,int fr){
    int vv;
    dp[u]=v[u];
    for (int i=0; i<way[u].size(); i++){
        vv=way[u][i];
        if (vv!=fr){
            solve_dfs(vv,u);
            dp[u]+=dp[vv];
            ans=min(ABS(summ-2*dp[vv]),ans);
        }
    }
    return ;
}

int main() {
    int cas=1;
    while (~scanf("%d%d",&n,&m)){
        if (n==0 && m==0) break;
        for (int i=0; i<100100; i++)
            way[i].clear();
        ans=linf;
        summ=0;
        for (int i=1; i<=n; i++){
            scanf("%lld",&v[i]);
            summ+=v[i];
        }
        int u,v;
        for (int i=0; i<m; i++){
            scanf("%d%d",&u,&v);
            way[u].pb(v);
            way[v].pb(u);
        }
        solve_dfs(1,-1);
        printf("Case %d: %lld\n",cas++,ans);
    }
    return 0;
}
