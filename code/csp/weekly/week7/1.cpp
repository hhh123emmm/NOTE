//浇水
#include<bits/stdc++.h>
using namespace std;

set<pair<long double,long double>> st1;
map<long double,long double> st;
int T;
int n,l,w;//组数，长度，宽度
long double w0;
int cnt=0;//最少需要喷水器
long double dis,pere;
int main(){
    freopen("E:\\Code\\code\\test.in","r",stdin);
    freopen("E:\\Code\\code\\test.out","w",stdout);
    cin>>T;
    for(int num=1;num<=T;num++){
        cnt=0;
        st1.clear();
        st.clear();
        cin>>n>>l>>w;
        w0=w*1.0/2;
        while(n!=0){
            cin>>dis>>pere;//距离和半径
            if(pere>w0) {
                long double temp=sqrtl(pere*pere-w0*w0),le,r;
                if(dis-temp<0) le=0;
                else le=dis-temp;
                if(dis+temp>l) r=l;
                else r=dis+temp;
                //st.insert({max(dis-temp,(0.0)),min(dis+temp,l*1.0)});
                st1.insert({le,r});
            }
            n--;
        }
        for(auto k=st1.begin();k!=st1.end();k++) cout<<"*"<<k->first<<"*"<<k->second<<endl;
        for(auto k=st1.begin();k!=st1.end();k++) st[k->first]=k->second;
        for(auto k=st.begin();k!=st.end();k++) cout<<"**"<<k->first<<"*"<<k->second<<endl;
        long double t=0,t1=0;
        auto i=st.begin();
        if(i==st.end()){cout<<"-1"<<endl;continue;}//空
        else t=i->second;
        if(i->first>0){cout<<"-1"<<endl;continue;}
        i++;
        if(t==0) {cout<<"-1"<<endl;continue;}//不存在0
        if(i==st.end()){//到结尾了
            i--;
            if(i->second>=l*1.0) {cout<<"1"<<endl;continue;}
            else{cout<<"-1"<<endl;continue;}//漏了
        }
        if(t>=l) {cout<<"1"<<endl;continue;}
        cnt++;
        //t!=0&&i!=st.end()
        t1=t;
        bool win=false;
        for(;i!=st.end();i++){
            //cout<<"*"<<i->first<<"*"<<i->second<<endl;
            if(i->first>t){
                //update
                if(i->first>t1){//fail
                    break;
                }
                else{
                    cnt++;
                    t=t1;
                    if(i->second>t1) t1=i->second;
                }
                if(t>=l){
                    win=true;
                    break;
                }
            }
            else{//i->first<=t
                t1=i->second>t1?i->second:t1;
                if(t1>=l){
                    win=true;
                    cnt++;
                    break;
                }
            }
        }
        if(win==false){
            cout<<"-1"<<endl;
        }
        else cout<<cnt<<endl;
    }
    return 0;
}