
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

            while (s <= e && arr[i] < deq[e])
                --e;

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

            while (s <= e && arr[i] > deq[e])
                --e;

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