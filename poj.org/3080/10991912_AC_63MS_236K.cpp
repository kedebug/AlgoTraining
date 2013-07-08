
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

string str[20];
int p[64];

void getp(string b)
{
    p[0] = -1;
    int j = -1;
    for (int i = 1; i < b.size(); ++i)
    {
        while (j != -1 && b[j+1] != b[i])
            j = p[j];
        if (b[j+1] == b[i])
            ++j;
        p[i] = j;
    }
}

int kmp(string a, string b)         // 返回b能匹配到a的最大长度
{
    getp(b);
    int j = -1;
    int ans = -1;
    for (int i = 0; i < a.size(); ++i)
    {
        while (j != -1 && b[j+1] != a[i])
            j = p[j];
        if (b[j+1] == a[i])
            ++j;
        if (j > ans)
            ans = j;
        if (j+1 == b.size())
            break;
    }
    return ans;
}

int main()
{
    int cases;
    cin >> cases;
    while (cases--)
    {
        int n, ans = 0;
        cin >> n;
        
        for (int i = 0; i < n; ++i)
            cin >> str[i];
        
        string outprint;

        for (int i = 0; i < 60; ++i)
        {
            string a, b;
            b = str[0].substr(i);
            int minmax = 100;

            for (int j = 1; j < n; ++j)     // 求后缀串能匹配到其它字符串的最大长度
            {
                a = str[j];
                int temp = kmp(a, b) + 1;
                if (temp < minmax)
                    minmax = temp;
            }
            if (minmax > ans)
                ans = minmax, outprint = str[0].substr(i, minmax);
            else if (minmax == ans && str[0].substr(i, minmax) < outprint)
                outprint = str[0].substr(i, minmax);
        }
        if (ans < 3) 
            cout << "no significant commonalities" << endl;
        else 
            cout << outprint << endl;
    }
    return 0;
}