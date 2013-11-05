
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1000010;
int arr[MAXN], deq[MAXN];

int main()
{
    int N, K;
    while (scanf("%d %d", &N, &K) != EOF)
    {
        for (int i = 1; i <= N; ++i)
            scanf("%d", &arr[i]);

        int s = 0, e = -1;

        for (int i = 1; i <= N; ++i)
        {
            if (i > K && arr[i-K] == deq[s])
                ++s;

            int l = s, r = e;
            while (l <= r)
            {
                int m = (l + r) >> 1;
                if (deq[m] <= arr[i])
                    l = m + 1;
                else
                    r = m - 1;
            }
            e = l - 1;

            deq[++e] = arr[i];

            if (i == K)
                printf("%d", deq[s]);
            else if (i > K)
                printf(" %d", deq[s]);
        }
        printf("\n");

        s = 0, e = -1;

        for (int i = 1; i <= N; ++i)
        {
            if (i > K && arr[i-K] == deq[s])
                ++s;

            int l = s, r = e;
            while (l <= r)
            {
                int m = (l + r) >> 1;
                if (deq[m] >= arr[i])
                    l = m + 1;
                else
                    r = m - 1;
            }
            e = l - 1;

            deq[++e] = arr[i];

            if (i == K)
                printf("%d", deq[s]);
            else if (i > K)
                printf(" %d", deq[s]);
        }
        printf("\n");
    }
    return 0;
}