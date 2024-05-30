//背包
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 5e6;
int n,c;

int w[maxn+30],v[maxn+30];
int f[2][maxn+30];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>c;
    int k=0;
    while(n--){
        int W,V,t;
        cin>>W>>V>>t;
        for(int i=1;t>0;t-=i,i*=2){
            int sz=min(t,i);
            //addItem(w*sz,v*sz);
            w[++k]=W*sz;
            v[k]=V*sz;
        }
    }
    for(int i=1;i<=k;++i){
        for(int j=c;j>=0;--j){
            f[i&1][j]=f[(i-1)&1][j];
            if(j>=w[i]) f[i&1][j]=max(f[i&1][j],f[(i-1)&1][j-w[i]]+v[i]);
        }
    }
    cout<<f[k&1][c];
    return 0;
}