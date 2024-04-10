//3个数
/*
a*b+1
(a*b+1)*c+1=a*b*c+c+1
(a*b*c+c+1)*d+1=a*b*c*d+c*d+d+1
abcde+cde+de+e+1
e*(d*(c+1)+1)
*/
//以上逻辑是错的，过了，但是我也没有看懂逻辑
#include<bits/stdc++.h>
using namespace std;

int n;
//vector<long long> arrayn;
long long sum1=1;
long long sum2=1;
long long M=0;
priority_queue<long long> q1;//max
priority_queue<long long,vector<long long>,greater<long long>> q2;//min
int main(){
    cin>>n;
    for(int i=0;i<=n;i++){
        long long temp;
        cin>>temp;
        if(i==n) break;
        //arrayn.push_back(temp);
        q1.push(temp);
        q2.push(temp);
    }
    //sort(arrayn.begin(),arrayn.end());//begin,end
    if(n<=2) M=0;
    else{
        //MAX,每次取最大的两个数-->得到的是最小值
        //int num1=n;
        while(q1.size()!=1){
            long long a=q1.top();
            q1.pop();
            long long b=q1.top();
            q1.pop();
            q1.push(a*b+1);
        }
        sum1=q1.top();
        q1.pop();
        //MIN
        while(q2.size()!=1){
            long long a=q2.top();
            q2.pop();
            long long b=q2.top();
            q2.pop();
            q2.push(a*b+1);
        }
        sum2=q2.top();
        q2.pop();
        M=abs(sum1-sum2);
    }
    cout<<M<<endl;
    return 0;
}
