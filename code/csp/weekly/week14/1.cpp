#include<bits/stdc++.h>
using namespace std;
//圆形？难评！--2n-1
const int maxn=3e2;
int n;
int f[maxn][maxn],g[maxn][maxn];
int sum[maxn];
int ans1,ans2;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        int temp;cin>>temp;
        sum[i]=sum[i-1]+temp;
    }
    for(int i=n+1;i<=2*n-1;i++) sum[i]=sum[i-1]+(sum[i-n]-sum[i-n-1]);
    //初始化
    memset(f,63,sizeof f);//0x3f
    for(int i=1;i<=2*n-1;++i) f[i][i]=0;
    memset(g,0,sizeof g);
    //状态转移
    for(int len =2 ;len<=n;++len){
        for(int i=1;i<=2*n-1-len+1;++i){
            int l=i,r=i+len-1;
            for(int k=l;k<r;++k){
               // f[l][r]=min(f[l][r],sum[l][r]+f[l][k]+f[k+1][r]);
               f[l][r]=min(f[l][r],sum[r]-sum[l-1]+f[l][k]+f[k+1][r]);
               g[l][r]=max(g[l][r],sum[r]-sum[l-1]+g[l][k]+g[k+1][r]);
            }
        }
    }
    ans1=f[1][n];
    for(int i=1;i<=n;i++) ans1=min(ans1,f[i][i+n-1]),ans2=max(ans2,g[i][i+n-1]);
    cout<<ans1<<"\n"<<ans2;
    return 0;
}