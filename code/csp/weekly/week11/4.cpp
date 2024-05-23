#include<bits/stdc++.h>
using namespace std;
#define lb(x) (x&-x)
#define ll long long
struct program{
    int t,s;
    program(int x,int y):t(x),s(y){}
    bool operator <(const program &another) const{
        return t<another.t or (t==another.t and s<another.s);
    }
};

const int maxn=1e6+3;
int n,s[maxn+1],sum[maxn];//桶排
vector<program> a;//?
int tt,ss;

inline ll ask(int p){//
    ll res=0;
    for(int i=p;i>=1;i-=lb(i)) res+=s[i];
    return res;
}

inline void upd(int p,int v){
    for(int i=p;i<=maxn;i+=lb(i)) s[i]+=v;//maxn?
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&tt,&ss);
        a.emplace_back(++tt,++ss);//??????????????????????????????????????????????????????
    }
    sort(a.begin(),a.end());//排序
    for(auto& i: a){
        sum[ask(i.s)]++;
        upd(i.s,1);
    }
    for(int i=0;i<n;i++) printf("%d\n",sum[i]);
    return 0;
}