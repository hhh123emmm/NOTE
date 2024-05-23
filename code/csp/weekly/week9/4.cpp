#include<bits/stdc++.h>
using namespace std;

const int maxn=1e6+30;

int m,n,d[maxn],f[maxn],vis[maxn],dcnt,fcnt,ans;
vector<int> G[maxn];
vector<int> fG[maxn];

void dfs(int x){
    d[x]=++dcnt;vis[x]=1;
    for(auto i:G[x]) if(!vis[i]) dfs(i);
    f[x]=++fcnt;
}

void dfs2(int x){
    vis[x]=1;
    for(auto i:G[x]) if(!vis[i]) dfs2(i);
}

void solve(){
    dcnt=fcnt=0;
    memset(vis,0,sizeof vis);
    for(int i=1;i<=n;i++) if(!vis[i]) dfs(i);
}

void solve2(){
    memset(vis,0,sizeof vis);
    for(int i=1;i<=n;i++) if(!vis[f[i]]) {dfs(f[i]);cout<<"*"<<f[i]<<endl;ans++;}
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int a,b;
        cin>>a>>b;
        G[a].push_back(b);
        fG[b].push_back(a);
    }
    solve();
    for(int i=1;i<=n;i++) d[f[i]]=i;//后序
    for(int i=1;i<=n;i++) f[i]=d[n-i+1];//逆后序
    memset(vis,0,sizeof vis);
    for(int i=1;i<=n;i++) if(!vis[f[i]]) {dfs2(f[i]);ans++;}
    cout<<ans<<"\n";
}

/*
1 3 2 4 5 9 8 6 7 10
3 1 9 5 4 2 8 6 7 10
10 7 6 8 2 4 5 9 1 3
10
7

*/