#include <iostream>
    #include <cstdio>
    #include <cstring>
    #include <cstdlib>
    using namespace std;
    const int M = 50010;
    long hd[M],nxt[2*M],to[2*M],cnt;
    int que[M];
    int T,e,v;
     long long w[2*M],dis[M],a[M];
    bool vis[M];
    void add(int x, int y, long long z)
    {
        to[cnt] = y;
        w[cnt] = z;
        nxt[cnt] = hd[x];
        hd[x] = cnt++;
    }
    void spfa()
    {
        int h = 1,t = 2;
        vis[1] = true;
        que[1] = 1;
        dis[1] = 0;
        while(h != t)
        {
            int sta = que[h++];
            vis[sta] = false;
            for(int i = hd[sta];~i; i = nxt[i])
                if(dis[to[i]] > dis[sta] + w[i] || dis[to[i]] == -1)
                {
                    dis[to[i]] = dis[sta] + w[i];
                    if(!vis[to[i]])
                    {
                        vis[to[i]] = true;
                        que[t++] = to[i];
                    }
                }
        }
    }
    int main()
    {
        scanf("%d", &T);
        while(T--)
        {
            memset(hd,-1,sizeof hd);
            memset(vis,false, sizeof vis);
            memset(dis,-1,sizeof dis);
            cnt = 0;
            scanf("%d%d", &v, &e);
            for(int i = 1; i <= v; i++) scanf("%lld", &a[i]);
            long long z;
            for(int i = 1,x,y; i <= e; i++) 
                scanf("%d%d%lld", &x, &y, &z),add(x,y,z),add(y,x,z);
            spfa();
            unsigned long long ans = 0;
            bool flag=1;
            for(int i = 1; i <= v; i++)
            {
                if(dis[i] == -1)
                {
                    flag = false;
                    break;
                }
                ans += a[i] * dis[i];
            }
            if(!flag)
            printf("No Answer\n");
            else
            printf("%lld\n", ans);
        }
        return 0;
    }