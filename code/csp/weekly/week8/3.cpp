//穿越
//n个秘密基地
//m条双向路径
//w个单向时空隧道 Ti/Tj

//F
//
#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+30;
const int inf=0x3f3f3f3f;
int n,m,w;
int l,r,lr;
int dis[maxn],vis[maxn],pre[maxn],cnt[maxn];

vector<pair<int,int>> edge[maxn];
bool spfa(int s){
    for(int i=1;i<=n;i++) dis[i]=inf,vis[i]=false,cnt[i]=0;
    dis[s]=0;vis[s]=true;//
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int x=q.front();q.pop();
        for(auto i:edge[x]){
            if(dis[i.first]>dis[x]+i.second){
                cnt[i.first]++;
                if(cnt[i.first]>=n) return true;
                dis[i.first]=dis[x]+i.second;
                pre[i.first]=x;
                if(!vis[i.first]){
                    vis[i.first]=true;
                    q.push(i.first);
                }
            }
        }
        vis[x]=false;
    }
    return false;
}
int main(){
    int F;
    cin>>F;
    while(F-->0){
        for(int i=0;i<maxn;i++) edge[i].clear();
        cin>>n>>m>>w;
        for(int i=1;i<=m;i++){
            cin>>l>>r>>lr;
            edge[l].push_back({r,lr});
            edge[r].push_back({l,lr});
        }
        for(int i=1;i<=w;i++){
            cin>>l>>r>>lr;
            edge[l].push_back({r,-lr});
        }
        bool istrue=false;
        for(int i=1;i<=n;i++){
            if(spfa(i)){
                istrue=true;
                break;
            }
        }
        cout<<(istrue==false?"NO":"YES")<<endl;
    }
}