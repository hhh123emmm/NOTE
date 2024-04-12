//找到最短的
//删除
#include<bits/stdc++.h>
using namespace std;
vector<long long> e;
priority_queue<int,vector<int>,greater<int>> p;

int n,m;
long long temp;

void initial(){
    int num=n;
    while(num!=0){
        cin>>temp;
        p.push(temp);
        num--;
    }
    int s=p.top();
    p.pop();
    while(p.size()!=0){
        int t=p.top();
        p.pop();
        e.push_back(t-s);
        s=t;
    }
    while(e.size()>=m){
        auto i=min_element(e.begin(),e.end());
        if((i+1)==e.end()){
            //i和i-1合并
            int sum=*i+*(i-1);
            *(i-1)=sum;
            e.erase(i);
            continue;
        }
        if(i==e.begin()){
            //i和i+1合并
            int sum=*i+*(i+1);
            *(i+1)=sum;
            e.erase(i);
            continue;
        }
        int sum=(*i+*(i-1))<(*i+*(i+1))?(*i+*(i-1)):(*i+*(i+1));
        *i=sum;
        e.erase((*(i-1)>*(i+1))?i+1:i-1);
    }
    sort(e.begin(),e.end());
    auto i=e.begin();
    temp=*i;
}
int main(){
    cin>>n>>m;//n-1段距离-->m-1段距离
    initial();
    cout<<temp<<endl;
    return 0;
}