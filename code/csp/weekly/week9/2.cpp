#include<bits/stdc++.h>
using namespace std;

const int maxn=1e6+30;
int n,m;
priority_queue<int,vector<int>,greater<int>> q;//小根堆
vector<int> ans;//存答案
int indeg[maxn];
vector<int> edge[maxn];
void toposort(){
    for(int i=1;i<=n;i++){
        if(indeg[i]==0) q.push(i);
    }
    while(!q.empty()){
        int u=q.top();q.pop();
        ans.push_back(u);
        for(auto v:edge[u]){
            if(--indeg[v]==0) q.push(v);
        }
    }
    for(int i=0;i<n;i++) cout<<ans[i]<<" ";
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        edge[u].push_back(v);
        indeg[v]++;
    }
    toposort();
    return 0;
}

//4->5
//2->3
//1->5