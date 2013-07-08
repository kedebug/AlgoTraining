#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
void MyScanf(int &num)
{
	char a;
    while(a=getchar(),!isdigit(a));
    num = a-'0';
    while ((a = getchar())!=' ' && a!='/n')
        num = num*10 + a-'0';
}
int a[101];
int n,m;
int status[101];
int num[101];
int status_num;
int f[2][61][61];
int ToInt(char buf[])
{
	int i;
	int result = 0;
	for (i = 0;i < m;i++)
		result = result * 2 + (buf[i] == 'H');
	return result;
}
void Input()
{
	char buf[1001];
	int i;
	for (i = 1;i <= n;i++)
	{
		scanf("%s",buf);
		a[i] = ToInt(buf);
	}
}
void GetAllStatus()
{
	int i;
	int temp;
	status_num = 0;
	for (i = 0;i < (1 << m);i++)
	{
		temp = i;
		if (temp & (temp << 1) || temp & (temp << 2)) continue;
		status[++status_num] = i;
		num[status_num] = 0;
		while (temp > 0)
		{
			num[status_num] += temp % 2;
			temp /= 2;
		}
	}
}
void Init()
{
	GetAllStatus();
	memset(f,0,sizeof(f));
}
void Print(int x)
{
	int i;
	for (i = 1;i <= m;i++)
	{
		cout << x % 2 << " ";
		x /= 2;
	}
}
void Compute()
{
	int i,j,k,p,now;
	now = 0;
	for (i = 1;i <= status_num;i++)
		if (status[i] & a[1])
			f[now][i][0] = 0;
		else
			f[now][i][0] = num[i];
//	Print(a[1]);
//	cout << endl;
//
//	for (i = 1;i <= status_num;i++)
//	{
//		cout << status[i] << " : ";
//		Print(status[i]);
//		cout << ": " << f[now][i][0] << endl;
//	}
	for (p = 2;p <= n;p++)
	{
		now = 1 - now;
		for (i = 1;i <= status_num;i++)
			for (j = 1;j <= status_num;j++)
			{
				if (status[i] & a[p] || status[i] & status[j])
					f[now][i][j] = 0;
				else
				{
					if (p == 2)
					{
						f[now][i][j] = num[i] + f[1 - now][j][0];
//						Print(status[i]);
//						cout << endl;
//						Print(status[j]);
//						cout << endl;
//						cout << f[now][i][j] << endl << endl;
					}
					else
					{
						for (k = 1;k <= status_num;k++)
							if (status[i] & status[k])
								continue;
							else
								f[now][i][j] = max(f[now][i][j],f[1 - now][j][k] + num[i]);
					}
				}
			}
	}
	int result = 0;
	for (i = 1;i <= status_num;i++)
		for (j = 1;j <= status_num;j++)
		{
			if (n == 1)
				result = max(result,f[now][i][0]);
			else
				result = max(result,f[now][i][j]);
		}
	cout << result << endl;
}
int main()
{
	while (cin >> n >> m)
	{
		Input();
		Init();
//		cout << status_num << endl;
		Compute();
	}
	return 0;
}
