#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4+30;
int n,m,T;
int l,r,mid;
int li,ri,c,d;
struct edge{
    int des,weight,t;
    bool operator<(const edge&b) const{
        return t>b.t;
    }
};
vector<edge> edges[maxn];//正向
int dis[maxn],vis[maxn];//溢出再改

priority_queue<edge> q;

bool dijkstra(){
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof vis);
    dis[1]=0;
    q.push(edge{1,0,0});
    while(!q.empty()){
        edge e=q.top();q.pop();
        int u=e.des;
        if(vis[u]) continue;
        vis[u]=1;
        for(auto i:edges[u]){
            int v=i.des;
            if(i.weight<mid) continue;//小的不满足
            if(dis[u]+i.t<dis[v]){
                dis[v]=dis[u]+i.t;
                q.push(edge{v,0,dis[v]});
            }
        }
    }
    if(dis[n]<=T) return true;
    else return false;
}
int binary_search(){
    //二分
    l=0;
    r=0x3f3f3f3f;
    while(l<=r){
        mid=(l+r+1)/2;
        if(dijkstra()){
            l=mid+1;
        }
        else r=mid-1;//////////////////////////////////////////////////////////////////
    }
    return l-1;
}

int main(){
    int F;
    cin>>F;
    while(F-->0){
        for(int i=0;i<=maxn;i++) edges[i].clear();
        cin>>n>>m>>T;
        for(int i=1;i<=m;i++){
            cin>>li>>ri>>c>>d;
            edges[li].push_back(edge({ri,c,d}));
            edges[ri].push_back(edge({li,c,d}));
        }
        cout<<binary_search()<<endl;
    }
}