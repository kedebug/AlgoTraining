/*
 ID: kedebug
 PROG: ride
 LANG: C++
*/

#include <stdio.h>
#include <limits.h>

#define DEBUG

int convert(const char* s) {
    int result = 1;
    while (*s != '\0') {
        result *= *s - 'A' + 1;
        s++;
        if (result * 2 > INT_MAX)
            result %= 47;
    }
    return result % 47;
}

int main() {
#ifdef DEBUG
    freopen("ride.in", "r", stdin);
    freopen("ride.out", "w", stdout);
#endif

    char comet[10];
    char group[10];

    scanf("%s", comet);
    scanf("%s", group);

    if (convert(comet) == convert(group))
        printf("GO\n");
    else
        printf("STAY\n");
}