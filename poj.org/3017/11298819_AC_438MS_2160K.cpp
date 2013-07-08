#include<stdio.h>
#include<string.h>
#define MAXD 100010
int T, N, node, left[MAXD], right[MAXD], size[MAXD], a[MAXD];
long long int M, key[MAXD], f[MAXD], A[MAXD];
int pool[MAXD], top, q[MAXD], d[MAXD];
void newnode(int &T, int v)
{
    if(top)
        T = pool[-- top];
    else
        T = ++ node;
    key[T] = v;
    size[T] = 1;
    left[T] = right[T] = 0;
}
void leftrotate(int &T)
{
    int k = right[T];
    right[T] = left[k];
    left[k] = T;
    size[k] = size[T];
    size[T] = size[left[T]] + size[right[T]] + 1;
    T = k;
}
void rightrotate(int &T)
{
    int k = left[T];
    left[T] = right[k];
    right[k] = T;
    size[k] = size[T];
    size[T] = size[left[T]] + size[right[T]] + 1;
    T = k;
}
void maintain(int &T, int flag)
{
    if(flag == 0)
    {
        if(size[left[left[T]]] > size[right[T]])
            rightrotate(T);
        else if(size[right[left[T]]] > size[right[T]])
            leftrotate(left[T]), rightrotate(T);
        else
            return ;
    }
    else
    {
        if(size[right[right[T]]] > size[left[T]])
            leftrotate(T);
        else if(size[left[right[T]]] > size[left[T]])
            rightrotate(right[T]), leftrotate(T);
        else
            return ;
    }
    maintain(left[T], 0);
    maintain(right[T], 1);
    maintain(T, 0);
    maintain(T, 1);
}
void Insert(int &T, int v)
{
    if(T == 0)
    {
        newnode(T, v);
        return ;
    }
    ++ size[T];
    if(v < key[T])
        Insert(left[T], v);
    else
        Insert(right[T], v);
    maintain(T, v >= key[T]);
}
int Delete(int &T, int v)
{
    -- size[T];
    if(key[T] == v || (v < key[T] && left[T] == 0) || (v >= key[T] && right[T] == 0))
    {
        int k = key[T];
        if(left[T] == 0 || right[T] == 0)
            pool[top ++] = T, T = left[T] + right[T];
        else
            key[T] = Delete(left[T], v + 1);
        return k;
    }
    if(v < key[T])
        return Delete(left[T], v);
    else
        return Delete(right[T], v);
}
int searchmin(int &T)
{
    if(left[T] == 0)
        return key[T];
    else
        return searchmin(left[T]);
}
int init()
{
    int i, ok = 1;
    T = node = top = left[0] = right[0] = size[0] = 0;
    A[0] = 0;
    for(i = 1; i <= N; i ++)
    {
        scanf("%d", &a[i]);
        A[i] = A[i - 1] + a[i];
        if(a[i] > M)
            ok = 0;
    }
    return ok;
}
void solve()
{
    int i, j, k, front, rear, decision;
    decision = front = rear = 0;
    for(i = 1; i <= N; i ++)
    {
        while(A[i] - A[decision] > M)
            ++ decision;
        while(front < rear && q[front] <= decision)
        {
            Delete(T, f[d[front]] + a[q[front]]);
            ++ front;
        }
        while(front < rear && a[i] >= a[q[rear - 1]])
        {
            Delete(T, f[d[rear - 1]] + a[q[rear - 1]]);
            -- rear;
        }
        q[rear] = i;
        if(front < rear)
            d[rear] = q[rear - 1];
        else
            d[rear] = decision;
        Insert(T, f[d[rear]] + a[i]);
        ++ rear;
        if(d[front] < decision)
        {
            Delete(T, f[d[front]] + a[q[front]]);
            d[front] = decision;
            Insert(T, f[decision] + a[q[front]]);
        }
        f[i] = searchmin(T);
    }
    printf("%lld\n", f[N]);
}
int main()
{
    while(scanf("%d%lld", &N, &M) == 2)
    {
        if(!init())
            printf("-1\n");
        else
            solve();
    }
    return 0;
}