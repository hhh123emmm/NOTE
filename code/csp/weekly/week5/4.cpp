#include<bits/stdc++.h>
using namespace std;

//单调栈
/*
while(!stack.empty() and stack.top()<=u) stack.pop();
stack.push(u);
单调递增栈，往左/往右第一个比当前元素大的元素。
单调递减栈，往左/往右第一个比当前元素小的元素
可以求得以当前元素为最值的最大区间
10 3 7 4 12
10                |10
3 10              |3
7 10              |7 3
4 7 10            |4 3
12                |12 4 3
左边第一个大       |左边第一个小
右边第一个大       |右边第一个小
最大矩形，左端点为l-往左数第一个小于此高度的值
         右端点为r-往右数第一个小于此高度的值

*/
const int MAX=1000000;
int n;//num
pair<int,int> Pair[MAX+30]={{0,0}};
long long maxarea;//MAX-
long long Height[MAX+30]={0};//0-1e+9
stack<int> STACK;
//bug 好像int*不出long,height改了对了
int main(){
    //freopen("E:\\Code\\code\\csp\\weekly\\week5\\in4.in","r",stdin);
    //freopen("E:\\Code\\code\\csp\\weekly\\week5\\out4.out","w",stdout);
    //cout<<"helloworld"<<endl;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>Height[i];
    maxarea=Height[1];
    Height[n+1]=0;//efficient border arrange
    for(int i=1;i<=n+1;i++){
        while(!STACK.empty() and Height[STACK.top()]>=Height[i]){
            int u=(STACK.top());//first right small index=i
            Pair[u].second=i;
            long long temp=(Pair[u].second-Pair[u].first-1)*Height[u];
            //cout<<" right-"<<i<<" left-"<<Pair[u].first<<endl;
            maxarea=max(maxarea,temp);
            STACK.pop();
        }
        if(STACK.empty()) Pair[i].first=0;
        else Pair[i].first=STACK.top();//index
        STACK.push(i);
        //cout<<i<<" i-first "<<Pair[i].first<<endl;
    }
    /*
    int i=n+1;
    while(!STACK.empty()){
        int u=(STACK.top());//first right small
        Pair[u].second=i;
        long long temp=(Pair[u].second-Pair[u].first-1)*Height[u];
        //cout<<" right-"<<i<<" left-"<<Pair[u].first<<endl;
        maxarea=max(maxarea,temp);
        STACK.pop();
    }
    */
    cout<<maxarea<<endl;
    return 0;
}