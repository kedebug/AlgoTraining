#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

#define lhs l, m, rt << 1
#define rhs m + 1, r, rt << 1 | 1

const int maxn = 131100;
bool hash[maxn];
int seg[maxn << 2];
int _xor[maxn << 2];

void DoXor(int rt)
{
    if (seg[rt] != -1)
        seg[rt] = seg[rt] ^ 1;
    else
        _xor[rt] = _xor[rt] ^ 1;
}

void PushDown(int rt)
{
    if (seg[rt] != -1)
    {
        seg[rt << 1] = seg[rt << 1 | 1] = seg[rt];
        _xor[rt << 1] = _xor[rt << 1 | 1] = 0;
        seg[rt] = -1;
    }
    if (_xor[rt])
    {
        DoXor(rt << 1);
        DoXor(rt << 1 | 1);
        _xor[rt] = 0;
    }
}

void Update(char op, int beg, int end, int l, int r, int rt)
{
    if (beg <= l && r <= end)
    {
        if (op == 'U')
            seg[rt] = 1, _xor[rt] = 0;
        else if (op == 'D')
            seg[rt] = 0, _xor[rt] = 0;
        else if (op == 'C' || op == 'S')
            DoXor(rt);
    } 
    else
    {
        PushDown(rt);
        int m = (l + r) >> 1;

        if (beg <= m)
            Update(op, beg, end, lhs);
        else if (op == 'I' || op == 'C')
            seg[rt << 1] = _xor[rt << 1] = 0;

        if (end > m)
            Update(op, beg, end, rhs);
        else if (op == 'I' || op == 'C')
            seg[rt << 1 | 1] = _xor[rt << 1 | 1] = 0;
    }
}

void Query(int l, int r, int rt)
{
    if (seg[rt] == 1)
    {
        for (int i = l; i <= r; ++i)
            hash[i] = true;
        return ;
    }
    else if (seg[rt] == 0 || l == r)
        return ;

    PushDown(rt);

    int m = (l + r) >> 1;
    Query(lhs); Query(rhs);
}

int main()
{
    seg[1] = _xor[1] = 0;

    char op, l, r;
    int a, b;
    while (scanf("%c %c%d,%d%c\n", &op, &l, &a, &b, &r) != EOF)
    {
        a <<= 1, b <<= 1;
        if (l == '(')
            ++a;
        if (r == ')')
            --b;

        if (a > b)
        {
            if (op == 'C' || op == 'I')
                seg[1] = _xor[1] = 0;
        }
        else
            Update(op, a, b, 0, maxn, 1);
    }

    Query(0, maxn, 1);

    bool flag = false;
    int s = -1, e;

    for (int i = 0; i < maxn; ++i) 
    {
        if (hash[i])
        {
            if (s == -1) s = i;
            e = i;
        } 
        else 
        {
            if (s != -1) 
            {
                if (flag) printf(" ");
                flag = true;
                printf("%c%d,%d%c",s&1?'(':'[' , s>>1 , (e+1)>>1 , e&1?')':']');
                s = -1;
            }
        }
    }
    if (!flag) printf("empty set");
    printf("\n");
    return 0;
}