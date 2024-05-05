//化学方程式 csp2019T3
#include<bits/stdc++.h>
using namespace std;

int n;//n个方程式

struct ele_set{
    map<string,int> mp;
    //元素集合，判断，合并

    bool operator==(const ele_set &other) const{
        return mp==other.mp;
    }

    void operator+=(const ele_set &other) {
        //for(auto &[k: const string, v:const int]: other.mp){
          //  mp[k]+=v;
        //}
        for(auto p:other.mp){
            mp[p.first]+=p.second;
        }
    }

    void operator*=(const int v){
        //for(auto &[k:const string,v0:int]:mp){
          //  v0*=v;
        //}
        for(auto p:mp){
            mp[p.first]*=v;
        }
    }
};

vector<string> split(string &t,char c){
    vector<string> res;//答案数组
    stringstream ss(t);
    string cur;
    while(getline(ss,cur,c)){//c指遇到换行/文件结尾停止，否则读入给cur，ss是输入流，通过c读给cur
        res.push_back(cur);
    }
    return res;
}

string r_el(string &s,int &p){
    //读元素，元素可以是一个大写字母/大写字母+1个小写字母
    string res;
    res+=s[p],++p;
    if(p<s.size() and islower(s[p])){ res+=s[p++];}
    return res;
}
int r_int(string &s,int &p){
    //读数字
    int res=0;
    while (p<s.size() and isdigit(s[p]))
    {
        res=res*10+s[p]-'0';
        ++p;
    }
    if(res==0) res=1;
    return res;
}
ele_set str2set(string &s,int &p){
    //字符串转化成元素数量集合
    ele_set res;
    int multi=r_int(s,p);
    while(p<s.size()){
        if(s[p]=='('){
            ++p;
            res+=str2set(s,p);//递归
        }else if(s[p]==')'){
            ++p;
            res*=r_int(s,p);
            break;
        }else{
            string el=r_el(s,p);
            res.mp[el]+=r_int(s,p);
        }
    }
    res*=multi;
    return res;
}

bool solve(string &s){
    vector<string> fms=split(s,'=');
    ele_set res[2];
    for(int i=0;i<2;++i){
        vector<string> terms =split(fms[i],'+');
        //for(auto &term: string & :terms){
        for(auto term:terms){
            int p=0;
            res[i]+=str2set(term,p);
        }
    }
    return res[0]==res[1];
}
int main(){
    string s;//方程式
    cin>>n;
    while(n--){
        cin>>s;
        if(solve(s)){
            cout<<"Y\n";//endl不如\n
        }else{
            cout<<"N\n";
        }
    }
}