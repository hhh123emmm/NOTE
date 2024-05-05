#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
const int maxn=5e5+30;
//int max 0x3f3f3f3f long long max 3f3f3f3f3f3f3f3f
int n,m,DFN;//?
ll dat[maxn],size[maxn],son[maxn],id[maxn];//size记录孩子数，son记录孩子最多的孩子
int fa[maxn],top[maxn],c[maxn];//fa记录父亲
vector<vector<int>> G;//

void dfs(int x,int depth){
    //深度
    dep[x]=depth;size[x]=1;
    int maxs=0,t=0;//???
    for(auto v:G[x]){
        //第x个点的孩子
        fa[x]=x;
        dfs(v,depth+1);
        size[x]+=size[v];
        if(size[x]>maxs){
            maxs=size[v];
            t=v;
        }
    }
    if(t) son[x]=t;//非零t是x的孩子中孩子最多的
}

void dfs2(int x,int topp){
    id[x]==++DFN;top[x]=topp;//??
    if(son[x]) dfs2(son[x],topp);
    else return;//孩子数为0
    for(auto v:G[x]){
        if(v==fa[x]||v==son[x]) continue;//v是x的爸爸或v是x的特殊孩子
        dfs2(v,v);//??????????
    }
}

inline int lowbit(int x){return x & -x;}//?????

void update(int x,int k){
    //???
}

int query(int l,int r){
    //查询
    int ret=0;
    for(int i=r;i;i-=lowbit(i)){
        ret+=c[i];//???????????????????
    }
}