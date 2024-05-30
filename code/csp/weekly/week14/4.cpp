#include<bits/stdc++.h>
using namespace std;
const int maxn=15;//2^15=65536
//n0d0c
//最少扣的分数/作业完成方案
//超1天，扣一分
int n;
int f[2^maxn];
int sum[2^maxn];
int c[maxn];//cost
int d[maxn];//deadline
int pre[maxn];//
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    //
    if(s&(1<<x)==0) f[s|(1<<x)]=f[s]+max(sum(s)+c[x]-d[x],0);
    return 0;
}