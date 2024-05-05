#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn=5e5+30;
int n,m,temp,op;//文件夹数量和操作次数
//父文件夹
//数据储存量
//op 1文件夹合并 2表示文件访问

//extern fileSys f[maxn];

struct fileSys{
    int father;
    vector<int> children;//
    ll disk;//存储量
    fileSys(){
        disk=0;
        father=0;
    }
    //void operator+=(const fileSys& other){}
};

fileSys f[maxn];
bool isdelete[maxn];

void merge(){
    cin>>temp;
    int num=f[temp].children.size();
    for(auto i:f[temp].children){
        //f[temp]+=f[i];
        f[temp].disk+=f[i].disk;
        //if(f[i].children.size()!=0)
        for(auto j:f[i].children){
            f[temp].children.push_back(j);
            f[j].father=f[i].father;
        }
        f[i].disk=0;
        f[i].father=-1;
        f[i].children.clear();
    }
    for(int i=1;i<=num;i++) f[temp].children.erase(f[temp].children.begin());
    //for(auto i:f[temp].children) cout<<i<<"*";
    cout<<f[temp].children.size()<<" "<<f[temp].disk<<"\n";
}
int dfs(int k,int sum){//这么写合并得处理干净
    if(f[k].father==0) return 1;
    k=f[k].father;
    sum=dfs(k,sum);
    return sum+1;
}
int main(){
    cin>>n>>m;
    for(int i=2;i<=n;i++){
        cin>>f[i].father;
        f[f[i].father].children.push_back(i);
    }
    for(int i=1;i<=n;i++){
        cin>>f[i].disk;
    }
    while(m--){
        cin>>op;
        if(op==1){
            //合并，输出子文件夹数量以及数据存储量
            merge();
        }else{
            //访问，获取数据最少经过的文件夹个数
            cin>>temp;
            cout<<dfs(temp,0)<<"\n";
        }
    }
}
/*
4 6
1 1 3
100 0 200 300
2 1
2 4
1 1
2 4
1 1
1 1
*/
/*
wule
*/