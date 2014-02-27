/*
 ID: kedebug
 PROG: gift1
 LANG: C++
 */

#include <stdio.h>
#include <map>
#include <string>
#include <vector>

using namespace std;

#define SUBMIT

int main() {
#ifdef SUBMIT
    freopen("gift1.in", "r", stdin);
    freopen("gift1.out", "w", stdout);
#endif

    int n;
    vector<string> names;
    map<string, int> money;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char name[20];
        scanf("%s", name);
        names.push_back(name);
        money[string(name)] = 0;
    }

    for (int i = 0; i < n; i++) {
        char name[20];
        int a, b;
        scanf("%s %d %d", name, &a, &b);

        if (a == 0 || b == 0) 
            continue;

        int c = a / b;
        for (int j = 0; j < b; j++) {
            char friends[20];
            scanf("%s", friends);
            money[string(friends)] += c;
        }

        money[name] -= c * b;
    }

    for (int i = 0; i < n; i++) {
        printf("%s %d\n", names[i].c_str(), money[names[i]]);
    }
}