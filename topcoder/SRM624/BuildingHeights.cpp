#include <vector>
#include <string>
using namespace std;

class BuildingHeights {
public:
    int minimum(vector<int>& heights) {
        sort(heights.begin(), heights.end());
        const int INF = 0x7FFFFFFF;
        vector<int> cost(heights.size(), INF);
        for (int i = 1; i < heights.size(); i++) {
            int acc = 0;
            for (int j = i - 1; j >= 0; j--) {
                acc += heights[i] - heights[j];
                cost[i-j] = min(cost[i-j], acc);
            }
        } 
        int result = 0;
        for (int i = 1; i < cost.size(); i++) {
            result ^= cost[i];
        }
        return result;
    }
};
