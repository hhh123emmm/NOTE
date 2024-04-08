#include<bits/stdc++.h>
using namespace std;

//BFS
int n;
const int MAX=1e5+5;
int reach[MAX]={-1};
int Len[MAX]={0};

struct Edge {
    int u,v,w;//u起点，v终点，w权重
};

vector<Edge> G[MAX];//邻接表
void addEdge(int u,int v){
    G[u].push_back({u,v,1});
    G[v].push_back({v,u,1});
}

void BFS(int u){
    queue<int> a;
    a.push(u);
    reach[u]=0;
    //int Length=0;
    while(!a.empty()){
        int temp=a.front();
        a.pop();
        for(auto i=G[temp].begin();i!=G[temp].end();i++){
            if(reach[i->v]==-1){
                a.push(i->v);
                reach[i->v]=reach[i->u]+1;
                //Length=max(Length,reach[i->v]);
            }
        }
    }
    //return Length;
}
int main(){
    cin>>n;
    Edge temp;
    int s=1,t=1;
    for(int i=1;i<n;i++){
        cin>>temp.u>>temp.v;
        addEdge(temp.u,temp.v);
    }
    memset(reach,-1,sizeof reach);//找起点
    BFS(s);
    for(int i=1;i<=n;i++) s=reach[s]>reach[i]?s:i;
    memset(reach,-1,sizeof reach);//找终点
    BFS(s);
    for(int i=1;i<=n;i++) Len[i]=max(reach[i],0);
    for(int i=1;i<=n;i++) t=reach[t]>reach[i]?t:i;
    memset(reach,-1,sizeof reach);//找终点
    BFS(t);
    for(int i=1;i<=n;i++) cout<<max(Len[i],reach[i])<<" ";
    cout<<endl;
    return 0;
}