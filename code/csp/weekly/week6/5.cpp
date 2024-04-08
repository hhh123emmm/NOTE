#include<bits/stdc++.h>
using namespace std;

const int MAX=1e5+5;
//n个田地 m个引水渠 一个抽水机p元
int n,m,p;
int f[MAX];//并查集
struct Edge{
    int u,v,w,next;
    bool operator<(const Edge &t) const { return w<t.w;}
} Edges[2*MAX];
//int head[MAX];
int tot;//tot是Edges的下标

void init(int num){
    //tot=1;
    //for(int i=0;i<n;i++) head[i]=-1;
    //memset(head,-1,sizeof head);
    for(int i=1;i<=num;i++) f[i]=i;
}
int find(int x){ //return f[x]==x?x:f[x]=find(f[x]);
    if(f[x]==x) return x;
    return f[x]=find(f[x]);
}
bool unite(int x,int y){
    x=find(x);y=find(y);
    if(x==y) return false;
    f[x]=y;
    return true;
}
void addEdge(int u,int v,int w){
    Edges[tot].u=u;
    Edges[tot].v=v;
    Edges[tot].w=w;
    //Edges[tot].next=head[u];//指向前一条边的下标
    //head[u]=tot;//更新为最新边下标
    tot++;//下标
}

long long kruskal_return_max(){
    sort(Edges+1,Edges+m+1);
    //int cnt=0,ans=0;爆了所有点。
    long long cnt=0,ans=0;
    for(int i=1;i<=m;++i){
        if(unite(Edges[i].u,Edges[i].v)){
            //ans = max(ans,Edges[i].w);
            ans+=Edges[i].w;
            if(++cnt==n-1) break;
        }
    }
    return cnt==n-1?ans:-1;
    //return ans;
}
int main(){
    cin>>n>>m>>p;
    init(n+1);
    for(int i=1;i<=m;i++){
        //int u,v,w;
        //cin>>u>>v>>w;
        //addEdge(u,v,w);
        cin>>Edges[i].u>>Edges[i].v>>Edges[i].w;
    }
    //超级源点
    for(int i=m+1;i<=m+n;i++) {//addEdge(n+1,i,p);
        Edges[i].u=n+1;
        Edges[i].v=i-m;
        Edges[i].w=p;
    }
    m+=n;
    n++;
    cout<<kruskal_return_max()<<endl;
    return 0;
}
