#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
#define INF 999999999
int head, n, m;
int sudo[9][9];
int num[350];
int cnt;
int ans[9][9];
 
struct node {
    int l, r, u, d;
    int c;
    int x, y, k;
 
    void set(int ll, int rr, int uu, int dd, int cc) {
        l = ll;
        r = rr;
        u = uu;
        d = dd;
        c = cc;
    }
} a[5000];
 
inline void add(int l, int x, int y, int k, int c) {
    cnt++;
    a[cnt].x = x;
    a[cnt].y = y;
    a[cnt].k = k;
    a[cnt].l = l;
    a[l].r = cnt;
    a[cnt].u = a[c].u;
    a[a[c].u].d = cnt;
    a[cnt].d = a[cnt].c = c;
    a[c].u = cnt;
    num[c]++;
}
 
inline void ad(int x, int y, int k) {
    add(cnt + 4, x, y, k, x * 9 + k);
    add(cnt, x, y, k, 81 + y * 9 + k);
    add(cnt, x, y, k, 162 + (x / 3 * 3 + y / 3)*9 + k);
    add(cnt, x, y, k, 243 + x * 9 + y + 1);
}
 
inline void make_map() {
    a[0].set(m, 1, 0, 0, 0);
    a[m].set(m - 1, 0, m, m, m);
    for (int i = 1; i < m; i++) {
        a[i].set(i - 1, i + 1, i, i, i);
    }
    cnt = m;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            for (int k = 1; k <= 9; k++) {
                if (sudo[i][j] != k && sudo[i][j] != 0)continue;
                n++;
                ad(i, j, k);
            }
}
 
inline void remove(int c) {
    a[a[c].r].l = a[c].l;
    a[a[c].l].r = a[c].r;
    int i, j;
    for (i = a[c].d; i != c; i = a[i].d) {
        for (j = a[i].r; j != i; j = a[j].r) {
            a[a[j].d].u = a[j].u;
            a[a[j].u].d = a[j].d;
            num[a[j].c]--;
        }
    }
}
 
inline void resume(int c) {
    a[a[c].r].l = c;
    a[a[c].l].r = c;
    int i, j;
    for (i = a[c].d; i != c; i = a[i].d) {
        for (j = a[i].r; j != i; j = a[j].r) {
            a[a[j].d].u = j;
            a[a[j].u].d = j;
            num[a[j].c]++;
        }
    }
}
 
bool dfs() {
    if (a[head].r == head)return 1;
    int min = INF;
    int c, i, j;
    for (i = a[head].r; i != head; i = a[i].r) {
        if (num[i] < min) {
            min = num[i];
            c = i;
        }
    }
    remove(c);
    for (i = a[c].d; i != c; i = a[i].d) {
        ans[a[i].x][a[i].y] = a[i].k;
        for (j = a[i].r; j != i; j = a[j].r) {
            remove(a[j].c);
        }
        if (dfs())return 1;
        for (j = a[i].l; j != i; j = a[j].l) {
            resume(a[j].c);
        }
    }
    resume(c);
    return 0;
}
 
int main() {
    int i, j;
    char s[20];
    int T;
    scanf("%d", &T);
    while (T--) {
        for (i = 0; i < 9; i++) {
            scanf("%s", s);
            for (j = 0; j < 9; j++) {
                sudo[i][j] = s[j] - '0';
            }
        }
        memset(num, 0, sizeof (num));
        head = 0;
        m = 27 * 9 + 81;
        n = 0;
        cnt = 0;
        make_map();
        if (!dfs())
            printf("Could not complete this grid.\n");
        else for (i = 0; i < 9; i++, printf("\n")) {
                for (j = 0; j < 8; j++)
                    printf("%d", ans[i][j]);
                printf("%d", ans[i][8]);
            }
        if (T != 0)printf("\n");
    }
}