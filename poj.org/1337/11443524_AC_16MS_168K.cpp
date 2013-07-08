#include <cstdio>
#include <algorithm>
#include <cstring> 
#include <map>
#include <vector> 
  
using namespace std;

vector<int> t[300];
int dp[400]; 
int l[300], a[300], d[300]; 
 

int main(){
    int ca,  n;
    scanf("%d", &ca);
    int maxt, mint; 
    while (ca--){
          scanf("%d", &n);
          for (int i = 1; i <= 250; i++)
                t[i].clear(); 
          maxt = -1, mint = 300; 
          for (int i = 0; i < n; i++){
              scanf("%d %d %d", &l[i], &a[i], &d[i]);
              maxt = max(maxt, d[i] -  l[i]);
              mint = min(mint, a[i]); 
              for (int j = a[i]; j + l[i] <= d[i]; j++)
                  t[j].push_back(i); 
          } 
          memset(dp, 0, sizeof(dp)); 
          for (int i = maxt; i >= mint; i--){
               if (t[i].empty())dp[i] = dp[i+1]; 
               else {
                      dp[i] = l[t[i][0]] + dp[i + l[t[i][0]]];
                      for (int j = 1; j < t[i].size(); j++){
                          dp[i] = min(dp[i], l[t[i][j]] + dp[i + l[t[i][j]]]);
                      }
               }
          }
          printf("%d\n", dp[mint]);
    }
    return 0;
} 
          
