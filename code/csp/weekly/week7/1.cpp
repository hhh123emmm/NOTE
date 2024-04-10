//浇水
#include<bits/stdc++.h>
using namespace std;

set<pair<int,int>> st;
int T;
int n,l,w;//组数，长度，宽度
int cnt=0;//最少需要喷水器
int dis,pere;
int main(){
    cin>>T;
    while(T!=0){
        cin>>n>>l>>w;
        while(n!=0){
            cin>>dis>>pere;//距离和半径
            if(pere*2>w) st.insert({max(dis-pere,0),min(dis+pere,n)});
        }
    }
}