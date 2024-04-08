#include<bits/stdc++.h>
using namespace std;
const int MAX=1000000;
int num[MAX+30]={0};
pair<int,int> maxmin[MAX+30]={{0,0}};
deque<int> minarray;//维护非递减的双端队列
deque<int> maxarray;//非递增

int n,k;
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>num[i];
    }
    for(int i=1;i<=n;i++){
        while(!minarray.empty() and minarray.front()<=i-k) minarray.pop_front();
        while(!minarray.empty() and num[minarray.back()]>num[i]) minarray.pop_back();
        minarray.push_back(i);//单调递增队列，丢弃大的
        while(!maxarray.empty() and maxarray.front()<=i-k) maxarray.pop_front();
        while(!maxarray.empty() and num[maxarray.back()]<num[i]) maxarray.pop_back();
        maxarray.push_back(i);//max,新加的数大，丢弃小的
        if(i>=k){
            maxmin[i-k+1].first=num[minarray.front()];
            maxmin[i-k+1].second=num[maxarray.front()];
        }
    }
    for(int j=1;j<=n-k+1;j++){
        cout<<maxmin[j].first<<" ";
    }
    cout<<endl;
    for(int j=1;j<=n-k+1;j++){
        cout<<maxmin[j].second<<" ";
    }
    cout<<endl;
    return 0;
}