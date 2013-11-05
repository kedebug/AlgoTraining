
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

const int maxd = 50010;
const int maxn = 11;

map<string, int> mp;
vector<int> w[maxn];
int dp[maxd];

int main()
{
    int m, n;
    while (scanf("%d %d", &m, &n) && m && n)
    {
        string s;
        mp.clear();
        for (int i = 0; i < m; ++i)
        {
            cin >> s;
            mp[s] = i;
            w[i].clear();
        }
        for (int i = 0; i < n; ++i)
        {
            int t;
            cin >> t >> s;
            w[mp[s]].push_back(t);
        }

        int ret = 0;
        for (int i = 0; i < m; ++i)
        {
            int sum = 0;
            for (int j = 0; j < w[i].size(); ++j)
                sum += w[i][j];

            memset(dp, 0, sizeof(int) * (sum + 1));

            for (int j = 0; j < w[i].size(); ++j)
                for (int v = sum >> 1; v >= w[i][j]; --v)
                    dp[v] = max(dp[v], dp[v-w[i][j]] + w[i][j]);

            ret += sum - dp[sum>>1];
        }
        printf("%d\n", ret);
    }
    return 0;
}