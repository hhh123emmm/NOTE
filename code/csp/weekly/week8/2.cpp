//买菜
//n-n
//为什么不TLE
#include<bits/stdc++.h>
using namespace std;

const int maxn=1e6+30;
int n;
int a[maxn]={0};

int l,r,sum;

int main(){
    cin>>n;
    for(int i=1;i<=2*n;i++){
        cin>>l>>r;
        for(int j=l;j<r;j++) a[j]++;
    }
    for(int i=1;i<=maxn;i++)
    if(a[i]==2) sum++;
    cout<<sum;
}