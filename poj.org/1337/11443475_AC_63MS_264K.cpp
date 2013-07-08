// 63 MS
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#define inf 1e9
#define N 110
using namespace std;
 
vector<int> G1[260];
int t[N], a[N], d[N];
int ans;
 
void DFS(int cur, int sum) {
//  当前时间、工作的总时间
    while (G1[cur].size() == 0 && cur <= 250)
        cur++;      // 当前时间点没有工作，则一直等待工作的到来
    if (cur > 250) { // 到达最终状态，比较总的工作时间
        ans = min(ans, sum);
        return;
    }
    for (int i = 0; i < G1[cur].size(); ++i) {
        int u = G1[cur][i];
        DFS(cur + t[u], sum + t[u]);
    }
}
 
int main() {
    int Case, n;
    cin>>Case;
    while (Case--) {
        memset(G1, 0, sizeof(G1));
        cin>>n;
        for (int i = 1; i <= n; ++i)
            cin>>t[i]>>a[i]>>d[i];
        //  构造一对多的映射关系，如果在当前时间i开始做第j个job能够完成，则构造对应边
        for (int i = 0; i <= 250; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (a[j] <= i && i + t[j] <= d[j])
                    G1[i].push_back(j);
            }
        }
        ans = inf;
        DFS(0, 0);
        cout<<ans<<endl;
    }
    return 0;
}