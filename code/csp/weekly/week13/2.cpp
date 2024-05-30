//背包
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e3;
int n,v;

int w[maxn+30],c[maxn+30];
int f[maxn+30];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>v;
    for(int i=1;i<=n;i++){
        cin>>w[i]>>c[i];
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=v;++j){
            if(j>=w[i]) f[j]=max(f[j],f[j-w[i]]+c[i]);
        }
    }
    cout<<f[v];
    return 0;
}