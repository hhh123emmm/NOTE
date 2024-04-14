#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAX_SIZE=1e6;
int num[MAX_SIZE];
int sum;
int asum[MAX_SIZE];//1-i
int bsum[MAX_SIZE];//i-n
int n,m;
//全局变量初始化为0
//1s,f(n)<1e8

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>num[i];
        sum+=num[i];
    }
    if(m==0){
        //
        for(int i=1;i<=n;i++){
        asum[i]=asum[i-1]+num[i];
    }
    for(int i=n;i>=1;i--){
        bsum[i]=bsum[i+1]+num[i];
    }
    int ans=0x3f3f3f3f3f3f3f;
    //
    for(int i=1;i<=n-1;i++){
        int l=asum[i-1];
        int r=bsum[i];
        int this_ans=max(l,r);
        ans=min(ans,this_ans);
    }
    cout<<ans<<endl;
    }
    else{
        //.-i-1  i-n
        int ans=0x3f3f3f3f3f3f3f3f;
        //int 3f3f3f
        //long long 3f3f3f3f3f3f3f3f
        for(int i=1;i<=n+1;i++){
            //
            //priority_queue<int,vector<int>,greater<int>> l_heap,r_heap;
            priority_queue<int> l_heap,r_heap;
            int l_sum=0,r_sum=0;
            for(int j=1;j<=i-1;j++){
                l_sum+=num[i];
                l_heap.push(num[i]);
            }
            for(int j=i;j<=n;++j){
                r_sum+=num[i];
                r_heap.push(num[i]);
            }

            for(int mm=0;mm<m;mm++){
                if(l_sum>r_sum){
                    //左边用
                    l_sum-=l_heap.top();
                    l_heap.pop();
                }else{
                    //you
                    r_sum-=r_heap.top();
                    r_heap.pop();
                }
            }
        int this_ans=max(l_sum,r_sum);
        ans=min(ans,this_ans);
        }
        cout<<ans<<endl;
    }
    //return int();
}