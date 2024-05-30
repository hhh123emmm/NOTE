//背包
#include<bits/stdc++.h>
using namespace std;
//#define int long long---？难评
const int maxn = 5e3;
int n,c;

int w[maxn+30],v[maxn+30];
int f[maxn+30];
vector<int> group[maxn+30];
int t;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>c;
    for(int i=1;i<=n;i++){
        int g;
        cin>>w[i]>>v[i]>>g;
        group[g].push_back(i);
        t=max(t,g);//组号
    }

    for(auto i=1;i<=t;++i){
        for(int j=c;j>=0;--j){
            for(int k:group[i])
             if(j>=w[k]) f[j]=max(f[j],f[j-w[k]]+v[k]);
        }
    }
    cout<<f[c];
    return 0;
}