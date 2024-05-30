#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=12;
int f[maxn][1<<maxn];
int h,w;

bool check(int i){
    bool continuous_0_parity = 0;    //连续0的个数的奇偶性，0为偶，1为奇
	bool has_continuous_odd_0 = 0;   //记录是否有奇数个连续0
    //暂时合法的
    for (int j = 0; j < w; j++)
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
			return false; //说明此状态是不合法的
    else return true;
}
    // * S&(1<<i) 非0就是存在的
    // * S=S | （1<<i) 添加1个位
    // * S=S ^ (1<<i) 删除，存在后再删
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>h>>w;
    f[0][0]=1;
    for(int i=1;i<=h;i++){//行
        for(int s1=0;s1<(1<<w);s1++){//列
            for(int s2=0;s2<(1<<w);s2++){
                if((s1&s2)!=0)continue;
                if(!check(s1|s2))continue;
                f[i][s1]+=f[i-1][s2];
            }
        }
    }
    if(h==0 || w==0) cout<<0<<"\n";
    else cout<<f[h][0]<<"\n";
    return 0;
}