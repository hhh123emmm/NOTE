#include<bits/stdc++.h>
using namespace std;

//按照喜爱度更改队伍的顺序，按照队伍的顺序输出
const string opid="OpId #";
int n,mn,top;//n是指令数，mn是日志，top是虚拟置顶
bool istop;
string op,msg;
int x;
vector<int> que;//队列
map<int,pair<long long,int>> mp;
int main(){
    freopen("E:\\Code\\code\\csp\\T3\\in.txt","r",stdin);
    freopen("E:\\Code\\code\\csp\\T3\\out.txt","w",stdout);
    int T;
    cin>>T;
    while(T-->0){
        mp.clear();
        que.clear();
        cin>>n;
        mn=0;
        istop=false;
        while(n-->0){
            cin>>op;
            if(op!="Prior"&&op!="Untop") cin>>x;
            //cout<<op<<" "<<x;
            if(op=="Add"){
                if(mp.find(x)==mp.end()){
                    //没有,可加
                    mp[x]={0,0};
                    que.push_back(x);
                    msg="success";
                }else{
                    //存在
                    msg="same likeness";
                }
            }else if(op=="Close"){
                if(mp.find(x)!=mp.end()){
                    //存在喜爱度
                    auto i=find(que.begin(),que.end(),x);
                    que.erase(i);
                    msg="close "+to_string(x)+" with "+to_string(mp[x].first);
                    mp.erase(x);
                    if(x==top) istop=false;
                    //删除操作----
                }else{
                    msg="invalid likeness";
                }
            }else if(op=="Chat"){
                if(istop){
                    mp[top].first+=x;
                    msg="success";
                }else{
                    if(!que.empty()){
                        mp[*que.begin()].first+=x;
                        msg="success";
                    }else{//kong
                        msg="empty";
                    }
                }
            }else if(op=="Rotate"){
                //将队列中第x个窗口放在队首
                x--;
                if(x>=0&&x<que.size()){
                    int c=que[x];
                    que.erase(que.begin()+x);
                    que.insert(que.begin(),c);//?
                    msg="success";
                }else{
                    msg="out of range";
                }
            }else if(op=="Prior"){
                if(que.empty()){
                    msg="empty";
                }else{
                    msg="success";
                    auto i=mp.end();
                    i--;
                    x=i->first;
                    auto j=find(que.begin(),que.end(),x);
                    que.erase(j);
                    que.insert(que.begin(),x);
                }
            }else if(op=="Choose"){
                if(mp.find(x)!=mp.end()){
                    //存在放到队首
                    msg="success";
                    auto i=find(que.begin(),que.end(),x);
                    que.erase(i);
                    que.insert(que.begin(),x);
                }else{
                    msg="invalid likeness";
                }
            }else if(op=="Top"){
                //如果喜爱度存在，则置顶
                if(mp.find(x)!=mp.end()){
                    msg="success";
                    istop=true;
                    top=x;
                }else{
                    msg="invalid likeness";
                }
            }else if(op=="Untop"){
                if(istop){//存在
                    istop=false;
                    msg="success";
                }else{
                    msg="no such person";
                }
            }else {
                cout<<"~invalid~"<<endl;
            }
            cout<<opid<<++mn<<": "<<msg<<"."<<"\n";
        }
        //与当前队列中所有说过话的窗口说拜拜
        if(istop&&mp[top].first!=0) cout<<opid<<++mn<<": "<<"Bye "<<top<<": "<<mp[top].first<<"."<<"\n";
        for(unsigned int i=0;i<que.size();i++){
            if(mp[que[i]].first!=0&&(!istop||(istop&&top!=que[i]))) cout<<opid<<++mn<<": "<<"Bye "<<que[i]<<": "<<mp[que[i]].first<<"."<<"\n";
        }
    }
    return 0;
}