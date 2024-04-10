# 最短路
## Floyd
用来求任意两个节点之间的最短路，时间复杂度高。
* 定义一个数组f[k][x][y]
```cpp
for(k=1;k<=n;k++){
    for(x=1;x<=n;x++){
        for(y=1;y<=n;y++){
            f[k][x][y]=min(f[k-1][x][y],f[k-1][x][k]+f[k-1][k][y]);
            //f[x][y]=min(f[x][y],f[x][k]+f[k][y]);
        }
    }
}
```
* $N^3$——1e2或者5e2
## Bellman-Ford算法
基于松弛操作的最短路算法，求有负权的图的最短路。
### 松弛操作
对于边(u,v)，松弛操作为$dis(v)=min(dis(v),dis(u)+w(u,v))$。尝试更新v点最短路的长度。当一次循环中没有成功的松弛操作，算法停止。
* 每次循环O(m)
* 最多会松弛n-1轮
### SPFA
只有上一次被松弛的点所连接的边，才有可能引起下一次的松弛操作
```cpp
struct edge{
    int v,w;
};
vector<edge> e[MAX];
int dis[MAX],cnt[MAX],vis[MAX];
queue<int> q;

bool spfa(int n,int s){
    memset(dis,63,sizeof dis);
    dis[s]=0;vis[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop;
        vis[u]=0;//?
        for(auto ed: e[u]){
            int v=ed.v,w=ed.w;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                cnt[v]=cnt[u]+1;//记录最短路经过的边数
                if(cnt[v]>=n) return false;
                if(!vis[v]) q.push(v),vis[v]=1;
            }
        }
    }
}
```