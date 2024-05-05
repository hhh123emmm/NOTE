#include<bits/stdc++.h>
using namespace std;

//"种下一瓶酸奶，长出好多酸奶"
const int maxn=1e3+30;
const int inf=0x3f3f3f3f;
int n,m;//n个坑，m条限制

//小于等于 大于等于 小于 大于 等于
//最多种多少瓶酸奶--跑最短路
//种酸奶，种酸奶，种下一瓶甜酸奶
//奶奶奶，哦，奶奶奶~~~

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
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int k,a,b,c;
        cin>>k>>a>>b>>c;
        if(k==1){
            //<= b-a  a->b
            edge[a-1].push_back({b,c});
        }else if(k==2){
            //>= b-a -- <= a-b b->a
            edge[b].push_back({a-1,-c});
        }else if(k==3){
            //<
            edge[a-1].push_back({b,c-1});
        }else if(k==4){
            edge[b].push_back({a-1,1-c});
        }else{
            edge[a-1].push_back({b,c});
            edge[b].push_back({a-1,-c});
        }
    }
    for(int i=1;i<=n;i++) edge[0].push_back({i,inf});
    if(spfa(0)) cout<<"impossible\n";
    else cout<<dis[n]-dis[n-1]<<"\n";
    return 0;
}
