#include<bits/stdc++.h>
using namespace std;

const int maxi=200000;
//map<char,int> mp[maxi+30];
char character[maxi+30];
int carray[27]={0};
int n;

int minin(){
    int index=1;
    for(int i=1;i<=26;i++)
    if(carray[index]>carray[i]) index=i;
    return carray[index];
}
int main(){
    cin>>n;
    int mini=n;
    int length=0;//26
    for(int i=1;i<=n;i++){
        cin>>character[i];
        //mp[i]=mp[i-1];
        //mp[i][character[i]]++;
        //if(mp[i].size()==26) mini=min(mini,i);
        if(carray[character[i]-'A'+1]==0){
            length++;
        }
        carray[character[i]-'A'+1]=i;
        if(length==26){
            int cmin=minin();
            //cout<<" *"<<i<<" "<<cmin<<"* ";
            mini=min(mini,i-cmin+1);
        }
    }
    //cout<<"initial: "<<mini<<" "<<endl;
    /*
    for(int i=mini;i<=n;i++){
        bool judge=false;
        int temp=0;
        int j;
        for(j=i-26;j>0;j--){
            judge=true;
            temp=j;
            for(auto k=mp[j].begin();k!=mp[j].end();k++)
            if((k->second)>=mp[i][k->first]){ 
                judge=false;
                break;
            }
        }
        if(judge==true){
            mini=min(i-temp,mini);
            //cout<<"i-"<<i<<"j-"<<temp<<" change: "<<mini<<endl;
        }
    }
    */
    cout<<mini<<endl;
    return 0;
}