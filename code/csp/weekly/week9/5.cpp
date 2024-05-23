#include<bits/stdc++.h>
using namespace std;

//DFS会爆时间的概率还挺高的--毫无意外的爆了
//爆了试试贪心吧/从边出发--正解是二分+spfa判负环
#define ll long long
#define eps 1e-5
const int maxn=2e3+30;

int n,m;
vector<pair<int,pair<int,int>>> G[maxn];
vector<pair<int,double>> g[maxn];
int vis[maxn];
double dis[maxn];

bool dfs(int s){
    vis[s]=1;
    for(auto i:g[s]){
        int v=i.first;
        double w=i.second;
        if(dis[s]+w<dis[v]){
            if(vis[v]) return true;
            else{
                dis[v]=dis[s]+w;
                vis[v]=true;
                if(dfs(v)) return true;
            }
        }
    }
    vis[s]=0;
    return false;
}

bool check(double mid){
    memset(dis,0x3f,sizeof dis);
    memset(vis,0,sizeof vis);
    for(int i=0;i<=n;i++) g[i].clear();
    for(int i=1;i<=n;i++){
        for(auto j:G[i]){
            g[i].push_back({j.first,mid*j.second.second-1.0*j.second.first});
        }
    }
    for(int i=1;i<=n;i++) g[0].push_back({i,0});
    dis[0]=0;
    vis[0]=1;
    return dfs(0);
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int s,t,v,p;
        scanf("%d%d%d%d",&s,&t,&v,&p);//防TLE
        G[s].push_back({t,{v,p}});
    }
    double l=0,r=210;
    while(r-l>=eps){
        double mid=(l+r)/2.0;
        if(check(mid)){
            l=mid;
        }else{
            r=mid;
        }
    }

    if(l==0) printf("-1");
    else printf("%.1lf\n",l);
    return 0;
}