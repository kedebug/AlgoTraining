#include<iostream>
using namespace std;
const int Max = 30;
bool map[Max][Max], vis[Max];
int n;
void dfs(int m){
    int queue[Max], tail, i, k;  // 所有能归于同一个channel的都压入queue中。
    tail = 1;
    queue[tail] = m;
    for(i = 1; i <= n; i ++)
        if(!vis[i] && !map[m][i]){
            bool add = true;
            for(k = 1; k <= tail; k ++)
                if(map[i][queue[k]]){
                add = false;
                break;
           }
           if(add){
                queue[++tail] = i;
                vis[i] = true;
           }
       }
}
int main(){
    while(cin >> n && n != 0){
        memset(map, false, sizeof(map));  // map[i][j] 记录转发器i和j是否相互干扰。
        memset(vis, false, sizeof(vis));  // vis[i] 记录转发器i是否已归于其中一个channel中。
        for(int i = 1; i <= n; i ++){
            char str[Max];
            cin >> str;
            for(int j = 2; str[j] != 0; j ++)
                map[i][str[j]-'A'+1] = true;
        }
        int ans = 0;
        for(int m = 1; m <= n; m ++)  // 逐个转发器归入channel中。
            if(vis[m] == false){
            vis[m] = true;
            dfs(m);
            ans ++;
        }
        if(ans == 1)  cout << ans << " channel needed." << endl;
        else   cout << ans << " channels needed." << endl;
    }
    return 0;
}