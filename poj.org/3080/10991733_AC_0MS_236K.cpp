#include <iostream>
#include <cstdio>
#include <string>
#include <cstdio>
using namespace std;
string s1, s2;
int next[100];
string s[20];
int kmp()
{
  memset(next, 0, sizeof(next));
  int len = s1.size();
  int ans = 0;
  next[0] = -1;
  int j = -1;
  for(int i = 1; i != len; i++)
  {
    while (j != -1 && s1[j+1] != s1[i]) j = next[j];
    if (s1[j+1] == s1[i]) j++;
    next[i] = j;
  }
  j = -1;
  for (int i = 0; i != 60; i++)
  {
    while (j != -1 && s1[j+1] != s2[i]) j = next[j];
    if (s1[j+1] == s2[i]) j++;
    if (j > ans) ans = j;   
    if (j == len) break; 
  }
  return ans;
}
int main()
{
  int l;
  cin >> l;
  while (l--)
  {
    int n;
    cin >> n;
    int ans = 0;
    string out;
    for (int i = 0; i != n; i++) cin >> s[i];
    for (int i = 0; i != 60; i++)
    {
      s1 = s[0].substr(i);
      int as = 100;
      for (int j = 1; j != n; j++)
      {
        s2 = s[j];
        int d = kmp()+1;
        if (d < as) as = d;            
      }
      if (as > ans)
      {
        ans = as;
        out = s[0].substr(i, as);        
      }
      else
      if (as == ans && s[0].substr(i, as) < out) out = s[0].substr(i, as); 
    }
    if (ans < 3) cout << "no significant commonalities" << endl;
    else cout << out << endl;
  }    
}