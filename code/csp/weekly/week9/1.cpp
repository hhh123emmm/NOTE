//这个题不能从两端遍历，得从中间往两边走
#include<bits/stdc++.h>
using namespace std;
int n;
string a;
int maxn;

bool yuanyicheck(int index){
    return a[index]=='a'||a[index]=='e'||a[index]=='i'||a[index]=='o'||a[index]=='u';
}

bool chekck(int l,int r){
    if(yuanyicheck(l)&&yuanyicheck(r)) return true;
    else if(a[l]==a[r]) return true;
    else return false;
}

int main(){
    cin>>n>>a;
    for(int i=0;i<=n-1;i++){
        //中心
        int m=i,l=i-1,r=i+1;
        while(l>=0&&r<=n-1){
            if(chekck(l,r)){
                maxn=max(maxn,r-l+1);
                l--;
                r++;
            }else{
                break;
            }
        }
        l=i,r=i+1;
        while(l>=0&&r<=n-1){
            if(chekck(l,r)){
                maxn=max(maxn,r-l+1);
                l--;
                r++;
            }else{
                break;
            }
        }
    }
    maxn=max(maxn,1);
    cout<<maxn<<endl;
}