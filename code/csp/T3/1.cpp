#include<bits/stdc++.h>
using namespace std;

int Num[100+30]={0};
//int Num[26][5]={0};
//int firstArrive[26][5]={0};
int A,B;//A*B张扑克牌，扑克牌是互异的。
int a1,b1,a2,b2;//已经拿走的两张牌
vector<pair<int,int>> record;//记录
int colornum[10]={0};
int sum=0;

bool explode2(){
    map<int,int> temp;
    temp[a1]++;
    temp[a2]++;
    temp[record[0].first]++;
    temp[record[1].first]++;
    temp[record[2].first]++;
    if(temp.size()==1) return 1;//都一样
    else if(temp[a1]==4||temp[a2]==4) return 1;//4个一样
    return 0;
}
bool sandaier3(){
    if(a1==a2){
        if(record[0].first==a1){
            return record[1].first==record[2].first;
        }
        else{
            return (record[1].first==a1)?(record[0].first==record[2].first):(record[0].first==record[1].first);
        }
    }
    else{
        if(record[0].first==a1){
            return ((record[1].first==a1)&&(record[2].first==a2))||((record[1].first==a2)&&(record[2].first==a1));
        }
        else{
            return (record[0].first==a2)&&(((record[1].first==a1)&&(record[2].first==a2))||((record[1].first==a2)&&(record[2].first==a1)));
        }
    }
}
bool tonghua4(){
    return (b1==b2)&&(b2==record[0].second)&&(record[0].second==record[1].second)&&(record[1].second==record[2].second);
}
bool shunzi5(){
    set<int> temp5;
    temp5.insert(a1);
    temp5.insert(a2);
    temp5.insert(record[0].first);
    temp5.insert(record[1].first);
    temp5.insert(record[2].first);
    if(temp5.size()<5) return 0;
    //if(temp5.pop)
    //temp5[0]
    auto i=temp5.begin();
    int lastValue=*i;
    i++;
    for(;i!=temp5.end();i++){
        if(*i-lastValue==1) lastValue=*i;
        else return 0;
    }
    return 1;
}
bool tonghuashun(){
    return tonghua4()&&shunzi5();
}
bool santiao6(){
    map<int,int> temp6;
    temp6[a1]++;
    temp6[a2]++;
    temp6[record[0].first]++;
    temp6[record[1].first]++;
    temp6[record[2].first]++;
    if(temp6.size()>3) return 0;
    else if(temp6[a1]>=3||temp6[a2]>=3||temp6[record[0].first]>=3) return 1;
    return 0;
}
bool liangdui7(){
    if(a1==a2) return (record[0].first==record[1].first)||(record[1].first==record[2].first)||(record[0].first==record[2].first);
    else{
        if(record[0].first==a1) return (a2==record[1].first)||(record[1].first==record[2].first)||(a2==record[2].first);
        else if(record[0].first==a2) return (a1==record[1].first)||(record[1].first==record[2].first)||(a1==record[2].first);
        else {
            if(record[1].first==record[0].first) return record[2].first==a1||record[2].first==a2;
            else if(record[2].first==record[0].first) return record[1].first==a1||record[1].first==a2;
            else return (record[2].first==a1&&record[1].first==a2)||(record[2].first==a2&&record[1].first==a1);
        }
    }
}
bool yidui8(){
    map<int,int> temp8;
    temp8[a1]++;
    temp8[a2]++;
    temp8[record[0].first]++;
    temp8[record[1].first]++;
    temp8[record[2].first]++;
    if(temp8.size()<=4) return 1;//存在一样的
    return 0;
}
void check(){
    bool is9=true;
    if(tonghuashun()){
        colornum[1]++;
        is9=true;
    }
    else{
        if(tonghua4()){
            colornum[4]++;
            is9=true;
        }
        if(shunzi5()){
            colornum[5]++;
            is9=true;
        }
    }
    if(explode2()){
        colornum[2]++;
        is9=true;
    }
    else{
        if(sandaier3()){
            colornum[3]++;
            is9=true;
        }
        else if(liangdui7()){
            colornum[7]++;
            is9=true;
        }
        else if(yidui8()){
            colornum[8]++;
            is9=true;
        }
    }
    if(santiao6()){
        colornum[6]++;
        is9=true;
    }
    if(is9==false) colornum[9]++;
}
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
            else istrue=1;
        }
    }
    colornum[istrue]++;
}
//void dfs(int abegin,int bbegin,int selection){
void dfs(int begin,int selection){
    //if(firstArrive[abegin][bbegin]==0){
      //  firstArrive[abegin][bbegin]=1;
    //}
    //else return;
    if(begin>A*B) return;
    if(selection==3){
        //选中3个数
        //check();
        cout<<"bb"<<begin/B+1<<begin%B<<" "<<record[0].first<<" "<<record[0].second<<"*"<<record[1].first<<" "<<record[1].second<<"*"<<record[2].first<<" "<<record[2].second<<" sum-"<<sum<<endl;
        check2();
        sum++;
    //    return;
    }
    //if(abegin>A||bbegin>B||selection>3) return;
    
    dfs(begin+1,selection);
    //dfs(abegin+1,bbegin,selection);//未选中1
    //dfs(abegin,bbegin+1,selection);//未选中2
    //if(Num[abegin][bbegin]==0){
    if(Num[begin]==0){
        //Num[abegin][bbegin]=1;
        Num[begin]=1;
        record.push_back({begin/B+1,begin%B});
        //record.push_back({abegin,bbegin});
        //if(selection!=2){
        //dfs(abegin+1,bbegin,selection+1);//选中1
        //dfs(abegin,bbegin+1,selection+1);//选中2
        dfs(begin+1,selection+1);
       // }
        //else {

       // }
        //Num[abegin][bbegin]=0;
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
    //Num[a1][b1]=1;
    //Num[a2][b2]=1;//标记选中
    //dfs(1,1,0);
    dfs(1,0);
    for(int i=1;i<=9;i++) cout<<colornum[i]<<" ";
    cout<<endl;
    cout<<sum<<endl;
    return 0;
}