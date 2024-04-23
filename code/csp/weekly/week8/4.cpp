#include<bits/stdc++.h>
using namespace std;

const int maxn=1e6+30;
vector<pair<int,int>> edge[maxn];//正向
vector<pair<int,int>> edges[maxn];//反向
long long dis[maxn],vis[maxn];
long long sum;

bool cmp(pair<int,int> &a,pair<int,int> &b){
    return a.second>b.second;//小的在前
}
priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(&cmp)> q(cmp);

void dijkstra(){
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof vis);
    dis[1]=0;
    q.push({1,0});
    while(!q.empty()){
        pair<int,int> e=q.top();q.pop();
        cout<<"***"<<e.first<<"***"<<e.second<<endl;
        int u=e.first;
        if(vis[u]) continue;
        vis[u]=1;
        for(auto i:edge[u]){
            int v=i.first;
            if(dis[u]+i.second<dis[v]){
                dis[v]=dis[u]+i.second;
                q.push({v,dis[v]});
            }
        }
    }
}
void redijkstra(){
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof vis);
    dis[1]=0;
    q.push({1,0});
    while(!q.empty()){
        pair<int,int> e=q.top();q.pop();
        
        int u=e.first;
        if(vis[u]) continue;
        vis[u]=1;
        for(auto i:edges[u]){
            int v=i.first;
            if(dis[u]+i.second<dis[v]){
                dis[v]=dis[u]+i.second;
                q.push({v,dis[v]});
            }
        }
    }
}
int n,m;
int l,r,lr;
int main(){
    int T;
    cin>>T;
    while(T-->0){
        sum=0;
        for(int i=0;i<maxn;i++){
            edge[i].clear();
            edges[i].clear();
        }
        cin>>n>>m;
        for(int i=1;i<=m;i++){
            cin>>l>>r>>lr;
            edge[l].push_back({r,lr});
            edges[r].push_back({l,lr});
        }
        dijkstra();
        for(int i=2;i<=n;i++){
            sum+=dis[i];
        }
        redijkstra();
        for(int i=2;i<=n;i++) sum+=dis[i];
        cout<<"*"<<sum<<endl;
    }
}