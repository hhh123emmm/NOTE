#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int maxn=1e6;
const int mm=998244353;

int n,m,k;
ll f[maxn+30],num[maxn+30];
ll h=0;

ll solve(){
    for(int i=1;i<=k;i++){//迈不到k阶
        num[i]=num[i-1];
        if(f[i]==-1) continue;
        f[i]=num[i]%mm;
        num[i]+=f[i];//k+1
        //f[i]%=mm;
        //num[i]%=mm;
    }
    for(int i=k+1;i<=n;i++){
        num[i]=num[i-1]-max(h,f[i-k-1]);//k
        if(f[i]==-1) continue;
        f[i]=num[i]%mm;
        num[i]+=f[i];//k+1  
        //f[i]%=mm;
        //num[i]%=mm;
    }
    return f[n];
}

//f[i] f[i-1]+...f[i-k] f[i+1]=f[i]-f[i-k]+f[i]
int main(){
    cin>>n>>m>>k;
    f[0]=1;num[0]=1;
    for(int i=1;i<=m;i++){int temp;scanf("%d",&temp); f[temp]=-1;}
    cout<<solve()%mm<<"\n";
    //for(int i=1;i<=n;i++) printf("%lld ",f[i]);
    return 0;
}