#include<bits/stdc++.h>
using namespace std;

//小写字母连续元音最长
//动态规划

int n;
int sum=0;
const int MAX=1e6;//1000000
char words[MAX+30]={0};

int main(){
    cin>>n;//n吗
    int record=0;
    bool lastChar=false;
    for(int i=1;i<=n;i++) {
        cin>>words[i];
        if(words[i]=='a'||words[i]=='e'||words[i]=='i'||words[i]=='o'||words[i]=='u'){
            lastChar=true;
            record++;
        }
        else{
            sum=max(sum,record);
            record=0;
            lastChar=false;
        }
    }
    cout<<sum<<endl;
}