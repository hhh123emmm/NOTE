#include<bits/stdc++.h>
using namespace std;

const int maxn=1000+30;
int n;//n个卖菜的商店 
int a[maxn]={0};
int b[maxn]={0};

int main(){
    int l,m,r;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        if(i==1) b[i]=(a[i]+a[i+1])/2;
        else if(i==n) b[i]=(a[i-1]+a[i])/2;
        else b[i]=(a[i-1]+a[i]+a[i+1])/3;
    }
    for(int i=1;i<=n;i++) cout<<b[i]<<" ";
}