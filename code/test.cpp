#include<bits/stdc++.h>
using namespace std;

int Num[100+30]={0};
int A,B;//A*B张扑克牌，扑克牌是互异的。
int a1,b1,a2,b2;//已经拿走的两张牌
vector<pair<int,int>> record;//记录
int colornum[10]={0};
int sum=0;

void check2(){
    int a3=record[0].first;
    int b3=record[0].second;
    int a4=record[1].first;
    int b4=record[1].second;
    int a5=record[2].first;
    int b5=record[2].second;
    int istrue=9;
    map<int,int> adaption;
    if(b1==b2 and b3==b4 and b5==b1 and b2==b3) istrue=4;//同花
    adaption[a1]++;
    adaption[a2]++;
    adaption[a3]++;
    adaption[a4]++;
    adaption[a5]++;
    if(adaption.size()==5){
        //每个数大小都不一样
        auto i=adaption.begin();
        int lastVlaue=i->first;
        i++;
        for(;i!=adaption.end();i++){
            if(i->first==lastVlaue+1) lastVlaue=i->first;
            else break;
        }
        if(i==adaption.end()) {
            if(istrue!=4) istrue=5;//顺子
            else {
                istrue=1;//同花顺
            }
        }
    }
    else{
        if(adaption.size()==4&&istrue!=4) istrue=8;//一对
        else if(adaption.size()==3&&istrue!=4){
            //三条/两对
            for(auto i=adaption.begin();i!=adaption.end();i++)
            if(i->second==3) {istrue=6;break;}//三条
            else if(i->second==2){istrue=7;break;}//两对
        }
        else if(adaption.size()<=2){
            //三带二/炸弹
            if(adaption[a1]==5||adaption[a1]==4||adaption[a1]==1) istrue=2;//炸弹
            else istrue=3;//三带二
        }
    }
    colornum[istrue]++;
}

void dfs(int begin,int selection){
    sum++;
    if(selection==3){
        //cout<<"bb"<<(begin-1)/B+1<<(begin-1)%B+1<<" "<<record[0].first<<" "<<record[0].second<<"*"<<record[1].first<<" "<<record[1].second<<"*"<<record[2].first<<" "<<record[2].second<<" sum-"<<sum<<endl;
        check2();
        //sum++;
        return;
    }    
    if(begin>A*B) return;
    dfs(begin+1,selection);//不选择
    if(Num[begin]==0){
        Num[begin]=1;
        record.push_back({(begin-1)/B+1,(begin-1)%B+1});
        dfs(begin+1,selection+1);
        Num[begin]=0;
        record.pop_back();//加入的顺序是优先大小，其次花色
    }
}

int main(){
    std::cin>>A>>B;//A是大小，B是花色。
    std::cin>>a1>>b1>>a2>>b2;
    a1++;
    a2++;
    b1++;
    b2++;
    Num[(a1-1)*B+b1]=1;
    Num[(a2-1)*B+b2]=1;
    dfs(1,0);
    for(int i=1;i<=9;i++) cout<<colornum[i]<<" ";
    cout<<endl;
    cout<<sum<<endl;
    return 0;
}