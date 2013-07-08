
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 20010 * 3;
int dp[maxn];

void zero1pack(int w, int value, int vol)
{
    for (int v = vol; v >= w; --v)
        dp[v] = max(dp[v], dp[v - w] + value);
}

int main()
{
    int cases = 0;
    while (++cases)
    {
        int arr[10], flag = 0, vol = 0;
        for (int i = 1; i <= 6; ++i)
        {
            scanf("%d", &arr[i]);
            flag |= arr[i];
            vol += arr[i] * i;
        }
        if (flag == 0)
            break ;

        if (vol & 0x01)
        {
            printf("Collection #%d:\nCan't be divided.\n\n", cases);
            continue;
        }

        memset(dp, 0, sizeof(dp));

        for (int i = 1; i <= 6; ++i)
        {
            int v = 1;
            while (v <= arr[i])
            {
                zero1pack(v * i, v * i, vol >> 1);
                arr[i] -= v;
                v <<= 1;
            }
            if (arr[i])
                zero1pack(arr[i] * i, arr[i] * i, vol >> 1);
        }

        if (dp[vol >> 1] == vol >> 1)
            printf("Collection #%d:\nCan be divided.\n\n", cases);
        else
            printf("Collection #%d:\nCan't be divided.\n\n", cases);
    }
    return 0;
}