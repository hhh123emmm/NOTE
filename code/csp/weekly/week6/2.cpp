#include<bits/stdc++.h>
using namespace std;

//小写字母连续元音最长
//动态规划

int n;
const int MAX=1e6;//1000000
char words[MAX+30]={0};
//char newwords[MAX+30]={0};
string newwords;

int main(){
    cin>>n;//n
    bool lastChar=false;
    for(int i=1;i<=n;i++) {
        cin>>words[i];
        if(words[i]=='a'||words[i]=='e'||words[i]=='i'||words[i]=='o'||words[i]=='u'){
            if(lastChar==false) newwords.push_back(words[i]);
            lastChar=true;
        }
        else{
            lastChar=false;
            newwords.push_back(words[i]);
        }
    }
    cout<<newwords<<endl;
}