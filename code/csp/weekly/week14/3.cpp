#include<bits/stdc++.h>
using namespace std;

const int maxn=4e3+30;

int n;
int f[maxn][maxn];
string s;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>s;
    n=s.size();

//     可以不连续，奇数长度/偶数长度
// * 字串
//     * bool f[i][j]
//     * f[i][j]=f[i+1][j-1]&(str[i]==str[j])
//     * max(j-i+1) f[i][j]==1
// * 子序列
//     * 长度为1一定是最长回文子序列
//     * 匹配
//         * f[i][j]=max(f[i+1][j],f[i][j-1])
//         * f[i][j]=f[i+1][j-1]+2
//     * f[1][n]
// * 状态量*转移复杂度，$O(n^2)$


    //初始化
    for(int i=1;i<=n;++i) f[i][i]=1;
    //状态转移
    for(int len =2 ;len<=n;++len){
        for(int i=1;i<=n-len+1;++i){
            int l=i,r=i+len-1;
            // cout<<s[l-1]<<s[r-1]<<(s[l-1]==s[r-1])<<"\n";
            if(s[l-1]==s[r-1]){ 
                f[l][r]=f[l+1][r-1]+2;
            }
            else{
                f[l][r]=max(f[l+1][r],f[l][r-1]);
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