#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,m;//h/l
ll maxsum=INT_MIN;
ll a[500+30][500+30];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin>>a[i][j];
    }
    for(int i1=1;i1<n;i1++){//行1
        for(int i2=i1+1;i2<=n;i2++){//行2
            ll s[500];
            for(int j=1;j<=m;j++){
                s[j]=a[i1][j]+a[i2][j];  
            }
            priority_queue<ll> pq(s,s+m);
            ll sum1=pq.top();pq.pop();
            ll sum2=pq.top();pq.pop();
            maxsum=max(maxsum,sum1+sum2);
        }
    }
    // for(int i=1;i<n;i++){
    //     for(int j=1;j<m;j++){
    //         for(int k=i+1;k<=n;k++){
    //             for(int p=j+1;p<=m;p++) {
    //                 ll temp=a[i][j]+a[i][p]+a[k][j]+a[k][p];
    //                 //cout<<temp<<" ";
    //                 maxsum=max(maxsum,temp);
    //             }
    //         }
    //     }
    // }
    cout<<maxsum;
    return 0;
}