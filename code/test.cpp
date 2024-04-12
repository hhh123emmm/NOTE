//二分，最大化最小值
#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+30;
int m,n,temp;//n个，m个
int muwu[maxn]={0};//----------------------1e9可能爆int？不太可能
int lef,righ,mid;
vector<int> dis;

int mini(){
    for(int i=1;i<=n-1;i++){
        dis.push_back(muwu[i]-muwu[i-1]);
    }
    sort(dis.begin(),dis.end());
    return dis[n-m];
}
bool check(){
    //当前值是否符合条件
    int cnt=0;
    int temp=muwu[0];//?
    for(int i=1;i<n;i++){
        if(muwu[i]-temp>=mid) {
            cnt++;
            temp=muwu[i];
            if(cnt>=m-1) break;
        }
    }
    return cnt>=m-1?true:false;
}

int binary_search(){
    //二分
    lef=mini();
    righ=(muwu[n-1]-muwu[0])/m+1;
    while(lef<righ){
        mid=(lef+righ+1)/2;
        if(check()){
            lef=mid;
        }
        else righ=mid-1;//////////////////////////////////////////////////////////////////
    }
    return lef;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>muwu[i-1];
    sort(muwu,muwu+n);
    cout<<binary_search()<<endl;
}