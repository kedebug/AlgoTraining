#include <stdio.h>
int main(void)
{
    int i, k, n;
    while(EOF != scanf("%d", &n), n)
    {
        switch (n % 6)
        {
        case 2:
        case 3:
            if(n % 2)k = (n - 1) / 2;
            else k = n / 2;
            if(n%2==0 && k%2==0)
            {
                for(i = k; i <= n; i+=2)
                    printf("%d ", i);
                for(i = 2; i <= k - 2; i+=2)
                    printf("%d ", i);
                for(i = k + 3; i <= n - 1; i+=2)
                    printf("%d ", i);
                for(i = 1; i <= k - 1; i+=2)
                    printf("%d ", i);
                printf("%d\n", k+1);
            }
            else if(k%2==0 && n%2)
            {
                for(i = k; i <= n - 1; i+=2)
                    printf("%d ", i);
                for(i = 2; i <= k - 2; i+=2)
                    printf("%d ", i);
                for(i = k + 3; i <= n - 2; i+=2)
                    printf("%d ", i);
                for(i = 1; i <= k + 1; i+=2)
                    printf("%d ", i);
                printf("%d\n", n);
            }
            else if(k%2 && n%2==0)
            {
                for(i = k; i <= n - 1; i+=2)
                    printf("%d ", i);
                for(i = 1; i <= k - 2; i+=2)
                    printf("%d ", i);
                for(i = k + 3; i <= n; i+=2)
                    printf("%d ", i);
                for(i = 2; i <= k - 1; i+=2)
                    printf("%d ", i);
                printf("%d\n", k+1);
            }
            else
            {
                for(i = k; i <= n - 2; i+=2)
                    printf("%d ", i);
                for(i = 1; i <= k - 2; i+=2)
                    printf("%d ", i);
                for(i = k + 3; i <= n - 1; i+=2)
                    printf("%d ", i);
                for(i = 1; i <= k + 1; i+=2)
                    printf("%d ", i);
                printf("%d\n", n);
            }
            break;
        default:
            if(n % 2 == 0)
            {
                for(i = 2; i <= n; i+=2)
                    printf("%d ", i);
                for(i = 1; i < n-1; i+=2)
                    printf("%d ", i);
                printf("%d\n", n-1);
            }
            else
            {
                for(i = 2; i <= n-1; i+=2)
                    printf("%d ", i);
                for(i = 1; i < n; i+=2)
                    printf("%d ", i);
                printf("%d\n", n);                
            }
            break;
        }
    }
    return 0;
}