 #include <iostream>
    #include <cstdio>
    #include <cstring>
    #include <cstdlib>
    #include <queue>
    using namespace std;
    const int Mv = 50010 ,Me = 2 * 50010;
    int hd[Mv],nxt[Me],to[Me],cnt;
    int size; 
    long long w[Me];
    long long dis[Mv];
    long long a[Mv];
    bool vis[Mv];
    int e,v,T; 
    struct Q
    {
        int node;
        long long dis;
        bool operator < (const Q &b) const{        //  heap的重载 < 号的形式。
            return dis > b.dis;
        }
    };
    void add(int x, int y, long long z)
    {
        to[cnt] = y;
        w[cnt] = z;
        nxt[cnt] = hd[x];
        hd[x] = cnt ++;
    }
    void dij(int s)
    {
        memset(vis,false,sizeof vis);
        memset(dis,0x7f,sizeof dis);
        dis[s] = 0;
        priority_queue<Q> que;
        Q a;
        a.node = s;
        a.dis = 0;
        que.push(a);
        //for(int i = 1; i <= v; i++)
        while(!que.empty())
        {
            int sta = que.top().node;
            que.pop();
            if(vis[sta]) continue;
            vis[sta] = true;
            //printf("%d : %d -> %lld\n",i,sta,dis[sta]);
            for(int i = hd[sta]; ~i; i = nxt[i])
                if(!vis[to[i]] && dis[to[i]] > dis[sta] + w[i])
                {
                    dis[to[i]] = dis[sta] + w[i];
                    Q now;
                    now.node = to[i];
                    now.dis = dis[to[i]];
                    que.push(now);    
                }
        }
    }
    int main()
    {
        scanf("%d", &T);
        while(T--)
        {
            memset(hd,-1,sizeof hd);
            cnt = 0;
            scanf("%d%d", &v, &e);
            for(int i = 1; i <= v; i++) scanf("%lld", &a[i]);
            long long z;
            for(int i = 1,x,y; i <= e; i++) 
                scanf("%d%d%lld", &x, &y, &z),add(x,y,z),add(y,x,z);
            dij(1);
            long long ans = 0;
            bool flag=1;
            for(int i = 1; i <= v; i++)
            {
                if(dis[i] == 0x7f7f7f7f7f7f7f7fll)
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