#include<cstdio>

//MAX_N 物品种类数最大值 MAX_n每种物品数目的最大值，MAX_V背包体积最大值
const int MAX_N = 101, MAX_V = 100004;

//w = v特例
inline void pack(bool f[], int V, int v, int n, int& total)
{
  //if (n == 0 || v == 0) return;
  if (n == 1) {  //01背包
    for (int i = V; i - v >= 0; --i)
      if (! f[i] && f[i - v]) f[i] = true, ++total;
    return;
  }
  if (n * v >= V - v + 1) {  //完全背包 n >= V / v
    for (int i = v; i <= V; ++i)
      if (! f[i] && f[i - v]) f[i] = true, ++total;
    return;
  }

  bool va[MAX_V];
  for (int j = 0; j < v; ++j) {     //多重背包
    bool *pb = va, *pe = va - 1; 
    size_t sum = 0;
    for (int k = j; k <= V; k += v) {
      if (pe == pb + n) sum -= *pb++;  //队列已满，队首元素出队
      *++pe = f[k];  //进队
      sum += f[k];     
      if (! f[k] && sum != 0) f[k] = true, ++total; 
      //f[k] = (bool)sum;       
    }
  }  
}

int main()
{
  //freopen("src.txt","r",stdin);
  //freopen("z-e.txt","w",stdout);
  int v[MAX_N], n[MAX_N];
  int V, N;
  bool f[MAX_V];
  while (scanf("%d %d",&N,&V) != EOF) {
    if (N + V == 0) break;
    for (int i = 0; i < N; ++i) scanf("%d", &v[i]);
    for (int i = 0; i < N; ++i) scanf("%d", &n[i]);
    int total = 0;
    f[0] = true;
    for (int i = 1; i <= V; ++i) f[i] = false;
    for (int i = 0; i < N; ++i) pack(f,V,v[i],n[i], total);
    printf("%d\n",total);
  }
}