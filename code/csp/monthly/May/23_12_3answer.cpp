#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn=2e3+30;
struct node{
    ll w;//自己
    ll sumw;//全部
    vector<int> son;//孩子
    //int cntson;//不需要，上者size
};
node a[maxn];

int n,m,test;//?
int p[maxn];//?
bool yes[maxn];//?

void doyes(int k){
    //递归查询 ???
    if(k==0) return;
    yes[k]=1;
    doyes(p[k]);
}

void dosum(int root){
    a[root].sumw=a[root].w;
    for(auto i: a[root].son){
        dosum(i);//递归计算权重和
        a[root].sumw+=a[i].sumw;
    }
}

ll ww(int root,int k){
    //差值
    ll ans=a[root].sumw-a[k].sumw;
    return abs(ans-a[k].sumw);
}

int findout(int root,int wwroot){
    //root当前根，wwroot计算差值的根
    int ans=root;
    for(int i:a[root].son){
        int temp=findout(i,wwroot);
        ll ww1=ww(wwroot,temp);
        ll ww2=ww(wwroot,ans);
        if(ww1<ww2||(ww1==ww2&&temp<ans)) ans=temp;//权重小或等序号小
    }
    return ans;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i].w;
    p[1]=0;//树？
    for(int i=2;i<=n;i++) cin>>p[i];
    while(m--){
        cin>>test;

        for(int i=1;i<=n;i++){
            yes[i]=0;
            a[i].son.clear();
            //a[i].cntson=0;
        }
        for(int i=2;i<=n;i++){
            a[p[i]].son.push_back(i);
        }
        dosum(1);//算权重和
        doyes(test);//把它和父亲设为1
        int root=1;
        while(a[root].son.size()>=1){
            int output=findout(root,root);//找到以root为计算差值的根的最小差值
            cout<<output<<" ";
            if(yes[output]){
                root=output;
            }else{
                //删除操作
                int fa=p[output];
                vector<int>::iterator re=find(a[fa].son.begin(),a[fa].son.end(),output);
                a[fa].son.erase(re);//删除
                while(fa!=p[root]){
                    a[fa].sumw-=a[output].sumw;
                    fa=p[fa];
                }
            }
        }
        cout<<"\n";
    }
}