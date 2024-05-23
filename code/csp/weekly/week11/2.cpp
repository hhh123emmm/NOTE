#include<bits/stdc++.h>
using namespace std;

int n,l,r;
multiset<int> st;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        st.insert(x);
    }
    l=*st.begin();
    r=*prev(st.end());
    if(n%2==1){
        int m;
        auto t=st.begin();
        for(int i=1;i<=n/2;i++) t++;
        m=*t;
        cout<<r<<" "<<m<<" "<<l<<endl;
    }else{
        auto t=st.begin();
        for(int i=1;i<n/2;i++) t++;
        auto s=t;s++;
        int m=(*t+*s);
        if(m%2!=0){
            if(m!=-1) cout<<r<<" "<<m/2<<".5 "<<l<<endl;
            else cout<<r<<" -"<<m/2<<".5 "<<l<<endl;
        }else{
            cout<<r<<" "<<m/2<<" "<<l<<endl;
        }
    }
    return 0;
}