#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1e6;
ll dp[maxn+30];
int cnt[maxn+30];
int n;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        int temp;cin>>temp;
        cnt[temp]++;
    }
    dp[0]=0;
    dp[1]=cnt[1];
    for(int i=2;i<=maxn;i++){
        dp[i]=max(dp[i-1],dp[i-2]+i*cnt[i]);
    }
    cout<<dp[maxn];
    return 0;
}