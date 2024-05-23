#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1e6+30;
int s[maxn],n,q;
#define lb(x) (x&-x)

ll ask(int p){
    ll res=0;
    for(int i=p;i>=1;i-=lb(i)) res+=s[i];
    return res;
}

void upd(int p,int v){
    for(int i=p;i<=n;i+=lb(i)) s[i]+=v;
}

int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++) {
        int temp;cin>>temp;
        upd(i,temp);
    }
    for(int i=1;i<=q;i++){
        int op,l,r;
        cin>>op>>l>>r;
        if(op==1) upd(l,r);
        else{
            cout<<ask(r)-ask(l-1)<<"\n";
        }
    }
    return 0;
}