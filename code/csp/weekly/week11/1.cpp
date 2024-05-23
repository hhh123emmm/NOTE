#include<bits/stdc++.h>
using namespace std;

const int maxn=1e6+30;
int r,y,g;
long long sum;
int n;//道路段数+红绿灯
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>r>>y>>g>>n;
    for(int i=1;i<=n;i++){
        int k,t;
        cin>>k>>t;
        if(k==0) sum+=t;
        else if(k==2) sum+=(t+r);
        else if(k==1) sum+=t;
        else sum+=0;
    }
    cout<<sum<<"\n";
    return 0;
}