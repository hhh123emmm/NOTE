#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn=2e3+30;
int n,m;//全部类别数量 需要测试的类别数量
ll sum;//权重和
//1是根
//n个，权重
//m个，需要测试的类别编号
int temp;

struct CataSys{
    int num;
    int myweight;//我的权重
    int childN;//孩子
    ll totalweight;//总权重
    vector<int> children;
    ll absw;//权重差绝对值
    CataSys(){
        myweight=0;
        childN=0;
        totalweight=0;
        absw=0;
    }
    bool operator<(const CataSys &other) const{
        return absw<other.absw;//小的为真
    }
    void operator+=(const CataSys &other){
        totalweight+=other.myweight;
        childN++;
        children.push_back(other.num);
        absw=abs(sum-totalweight-totalweight);
    }
}root;
CataSys cata[maxn];

map<CataSys,int> mp;

void process(){
    cin>>temp;
    ll sumt=sum;
    for(int i=1;i<=n;i++){
        mp[cata[i]]=cata[i].absw;
    }
    auto i=mp.begin();cout<<i->first.num<<" ";
    if(i->first.num==temp) return;
    if(find(i->first.children.begin(),i->first.children.end(),temp)!=0)

}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>cata[i].myweight;
        cata[i].totalweight=cata[i].myweight;
        cata[i].num=i;
        sum+=cata[i].myweight;
    }
    for(int i=2;i<=n;i++){
        cin>>temp;
        cata[temp]+=cata[i];
    }
    for(int i=1;i<=m;i++){
        process();
    }
}