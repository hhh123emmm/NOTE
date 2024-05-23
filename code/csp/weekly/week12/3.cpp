#include<bits/stdc++.h>
using namespace std;

#define int long long
const int maxn=1e6;
//矩阵选数 3行n列
int n;
int dp[maxn+30][3];
int a[3][maxn+30];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for(int i=0;i<3;i++){
        for(int j=1;j<=n;j++) cin>>a[i][j];
    }
    dp[1][0]=0,dp[1][1]=0,dp[1][2]=0;
    for(int i=2;i<=n;i++){
        dp[i][0]=min(dp[i-1][0]+abs(a[0][i]-a[0][i-1]),min(dp[i-1][1]+abs(a[0][i]-a[1][i-1]),dp[i-1][2]+abs(a[0][i]-a[2][i-1])));//0表示选的第0个数
        dp[i][1]=min(dp[i-1][0]+abs(a[1][i]-a[0][i-1]),min(dp[i-1][1]+abs(a[1][i]-a[1][i-1]),dp[i-1][2]+abs(a[1][i]-a[2][i-1])));//1表示选的第1个数
        dp[i][2]=min(dp[i-1][0]+abs(a[2][i]-a[0][i-1]),min(dp[i-1][1]+abs(a[2][i]-a[1][i-1]),dp[i-1][2]+abs(a[2][i]-a[2][i-1])));//2表示选的第2个数 
    }
    cout<<min(dp[n][0],min(dp[n][1],dp[n][2]));
    return 0;
}