//背包
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e3;
int n,v;

int w[maxn+30],c[maxn+30],state[maxn+30];
int f[2][maxn+30];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>v;
    for(int i=1;i<=n;i++){
        cin>>w[i]>>c[i];
    }
    // for(int i=1;i<=n;++i){
    //     for(int j=v;j>=0;--j){
    //         f[i&1][j]=f[(i-1)&1][j];
    //         if(j>=w[i]) f[i&1][j]=max(f[i&1][j],f[(i-1)&1][j-w[i]]+c[i]);
    //     }
    // }
    for(int i=1;i<=n;++i){
        for(int j=v;j>=0;--j){
            f[i&1][j]=f[(i-1)&1][j];
            if(j>=w[i]) f[i&1][j]=max(f[i&1][j],f[(i-1)&1][j-w[i]]+c[i]);
            if(f[i&1][j]==f[(i-1)&1][j]) state[i]=0;
            else state[i]=1;
        }
    }
    cout<<f[n&1][v]<<'\n';
    for(int i=1;i<=n;i++)  cout<<state[i]<<" ";
    return 0;
}

// void ddd(int i,int j){
//     if(i>=0){
//         if(f[i][j]==f[i-1][j]){
//             state[i]=0;
//             ddd(i-1,j);
//         }else if(j-w[i]>=0&&f[i][j]==f[i-1][j-w[i]+c[i]]){
//             state[i]=1;
//             ddd(i-1,j-w[i]);
//         }
//     }
// }