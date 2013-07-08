#include<iostream>
#include<cstdio>
#include<vector>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;
const int MAX = 52;
const int INF = 99999999;
 
int miDp[MAX][MAX];
int maDp[MAX][MAX];
 
int main(){
    int n, i, j, k, num, ans;
    char sym[MAX];
    vector<int> vec;
    cin >> n;
    for(i = 0; i < n; i ++){
        cin >> sym[i] >> num;
        maDp[1][i] = miDp[1][i] = num;
    }
    for(i = 2; i <= n; i ++)
        for(j = 0; j < n; j ++){
            maDp[i][j] = -INF;
            miDp[i][j] = INF;
            for(k = 1; k < i; k ++){
                if(sym[(k+j)%n] == 't'){
                    maDp[i][j] = max(maDp[i][j],
                        maDp[k][j]+maDp[i-k][(k+j)%n]);
                    miDp[i][j] = min(miDp[i][j],
                        miDp[k][j]+miDp[i-k][(k+j)%n]);
                }else{
                    maDp[i][j] = max(maDp[i][j],
                        max(maDp[k][j]*maDp[i-k][(k+j)%n], miDp[k][j]*miDp[i-k][(k+j)%n]));
                    miDp[i][j] = min(miDp[i][j], min(
                        min(maDp[k][j]*maDp[i-k][(k+j)%n], miDp[k][j]*miDp[i-k][(k+j)%n]),
                        min(maDp[k][j]*miDp[i-k][(k+j)%n], miDp[k][j]*maDp[i-k][(k+j)%n])));
                }
            }
        }
    ans = -INF;
    for(i = 0; i < n; i ++){
        if(maDp[n][i] == ans){
            vec.push_back(i);
        }else if(maDp[n][i] > ans){
            ans = maDp[n][i];
            vec.clear();
            vec.push_back(i);
        }
    }
    printf("%d\n", ans);
    for(i = 0; i < vec.size(); i ++)
        printf("%d ", vec[i]+1);
    printf("\n");
    return 0;
}