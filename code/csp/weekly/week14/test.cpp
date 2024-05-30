/*
 * @Description: Mesh Filling Problem
 * @Author: Zhoujin - SDU
 * @email: 1761806916@qq.com
 * @Date: 2021-05-27 13:23:27
 * @LastEditTime: 2021-05-27 13:23:27
 * @FilePath: \week13\t4.cpp
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#include <bitset>
#define ll long long 
using namespace std;
const int Max = 12;
ll dp[Max][1 << Max];
bool legal[1 << Max];
int n, m, cnt;

void show_dp()
{
	cout << "dp : " << endl;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < (1 << m); j++)
			cout << dp[i][j] << " ";
		cout << endl;
	}
}

void solve()
{
	//对于m列，有[0, 2^m)个二进制序列，先把十进制数转二进制序列，再判断是否有连续奇数个0
	for (int i = 0; i < (1 << m); i++)
	{
		bool continuous_0_parity = 0;    //连续0的个数的奇偶性，0为偶，1为奇
		bool has_continuous_odd_0 = 0;   //记录是否有奇数个连续0
		legal[i] = 1;                    //暂时记录状态i是合法的
		for (int j = 0; j < m; j++)
		{
			if ((i >> j) & 1)   //出现1
			{
				if (continuous_0_parity == 1)   //有连续个级数0
					has_continuous_odd_0 |= continuous_0_parity;
				continuous_0_parity = 0;    //奇偶性置空，重新计算奇偶性
			}
			else     //出现0
				continuous_0_parity ^= 1;   //奇偶性取反
		}
		if (continuous_0_parity | has_continuous_odd_0)   //如果整段中出现了奇数个0
			legal[i] = 0;      //说明此状态是不合法的
		//否则就是合法的
	}

	cout << "Legal cases: ";
	for (int i = 0; i < (1 << m); i++)
		if (legal[i])
			cout << bitset<sizeof(i)>(i) << " ";
	cout << endl << endl;
	dp[0][0] = 1;   //初始状态，第0行的全0状态肯定是合法的
	for (int i = 1; i <= n; i++)     //遍历每一行
	{
		cout << "row = " << i << endl;
		for (int j = 0; j < (1 << m); j++)      //枚举当前行的所有状态
		{
			dp[i][j] = 0;
			for (int k = 0; k < (1 << m); k++)  //枚举之前行的所有状态
			{
				if (legal[k | j] && ((k & j) == 0))
				{
					cout << "State i: " << bitset<sizeof(j)>(j) << endl;
					cout << "      k: " << bitset<sizeof(k)>(k) << endl;
					cout << "update dp[" << i << "][" << j << "] "
						<< "from " << dp[i][j];
					dp[i][j] += dp[i - 1][k];
					cout << " to " << dp[i][j] << endl;
				}
			}
		}
		cout << endl;
		cout << endl;
	}

	//show_dp();
}

int main()
{
	cin >> n >> m;

	solve();
	if (n == 0 || m == 0)
		cout << 0 << endl;
	else
		cout << dp[n][0] << endl;

	return 0;
}
