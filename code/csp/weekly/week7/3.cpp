//这题目和图相关？
//找到最短的一条边，将它和它两边较短的一条边合并
#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+30;

struct edge{
    int u,v,w,i;
    bool operator<(const edge &e)const {return w<e.w;}
}Edges[maxn];//写着玩
int jud[maxn];
int n,m;
int shortest;
priority_queue<long long,vector<long long>,greater<long long>> quen;
priority_queue<edge,vector<edge>,greater<edge>>quem;

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        long long temp;
        cin>>temp;
        quen.push(temp);//坐标
    }
    int index=0;
    int s=quen.top();
    quen.pop();
    while(quen.size()!=0){
        int t=quen.top();
        quen.pop();
        Edges[++index].u=s;
        Edges[index].v=t;
        Edges[index].w=t-s;
        Edges[index].i=index;
        jud[index]=index;
        quem.push(Edges[index]);
        s=t;
    }
    int num=n-1;
    while(num>=m){//m-1个距离
        edge a=quem.top();
        quem.pop();
        int k=a.i;
        int l,r;
        if(k>2&&k<index){
            if(jud[k-1]==k-1)
                l=Edges[k-1].w;
            else l=Edges[]
        }
        num--;
        //
    }
    return 0;
}