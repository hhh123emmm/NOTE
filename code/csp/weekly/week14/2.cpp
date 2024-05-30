#include<bits/stdc++.h>
using namespace std;

const int maxn=1e2+30;

int n;
int f[maxn][maxn];
string s;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>s;
    n=s.size();
//      f[i][j]=min{f[i][k]+f[k+1][j]}
// * f[i][j]=min{f[i][j],f[i+1][j-1]}
// * 初始化，长度为1答案为1，长度为0为0
// * 匹配
//     * 不匹配f[i][j]=min{f[i][k]+f[k+1][j]}
//     * 匹配f[i][j]=min{f[i][j],f[i+1][j-1]}
// * answer：f[1][n]
    //初始化
    memset(f,0x3f,sizeof f);//0x3f
    for(int i=1;i<=n;++i) f[i][i]=1;
    for(int i=1;i<=n;++i){
        for(int j=i-1;j>=1;--j) f[i][j]=0;
    }
    //状态转移
    for(int len =2 ;len<=n;++len){
        for(int i=1;i<=n-len+1;++i){
            int l=i,r=i+len-1;
            // cout<<s[l-1]<<s[r-1]<<(s[l-1]==s[r-1])<<"\n";
            if(((s[l-1]=='['&&s[r-1]==']')||(s[l-1]=='('&&s[r-1]==')'))){ 
                f[l][r]=min(f[l][r],f[l+1][r-1]);
                for(int k=l;k<r;++k) f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]);
            }
            else{
                for(int k=l;k<r;++k) f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]);
            } 
        }
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++) cout<<f[i][j]<<" ";
    //     cout<<s[i-1]<<"\n";
    // }
    cout<<f[1][n];
    return 0;
}