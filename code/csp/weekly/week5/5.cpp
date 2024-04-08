#include<bits/stdc++.h>
using namespace std;
const int MAX=100000;
int n,m;
int l,r;//c:1-100
int pren[26]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
long long c=1,d=1,p=1e9+7;
long long NNum[MAX+30][25+2]={0};//存个数
long long preNUM[25+2]={p};

long long qpow(long long a,long long b){
    //a%=p;
    //b%=p;
    if(!b) return 1;//b==0
    long long now=qpow(a,b/2);
    now%=p;
    if(b&1) return a*now%p*now%p;
    else return now*now%p;
}
int main(){
    //freopen("E:\\Code\\code\\csp\\weekly\\week5\\in4.in","r",stdin);
    //freopen("E:\\Code\\code\\csp\\weekly\\week5\\out4.out","w",stdout);
    //cout<<"helloworld"<<endl;
    //cout<<1e+9<<endl;
    //cout<<p<<endl;
    //p=p+7;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>l>>r>>c>>d;
        int temp=1;
        while(c!=1){
            for(int j=temp;j<=25;j++){
                if(pren[j]>c) break;
                if(c%pren[j]==0){
                    temp=j;
                    c/=pren[j];
                    NNum[l][j]+=d;
                    NNum[r+1][j]-=d;
                    //NNum[l][j]%=p;
                    //NNum[r+1][j]%=p;
                    break;
                }
            }
        }
        //分解因式
    }
    for(int i=1;i<=25;i++) preNUM[i]=NNum[1][i];
    //up want to 差分
    for(int i=1;i<=n;i++){
        for(int j=1;j<=25;j++)
        {
            NNum[i][j]+=NNum[i-1][j];
            //NNum[i][j]%=p;
            //if(NNum[i][j]!=0)
            preNUM[j]=min(NNum[i][j],preNUM[j]);
        }
    }
    long long sum=1;
    for(int i=1;i<=25;i++){
        //cout<<"i-"<<i<<"num-"<<preNUM[i]<<endl;
        if(preNUM[i]!=0){
            sum*=qpow(pren[i],preNUM[i]);
            sum%=p;
        }
    }
    cout<<sum<<endl;
    return 0;
}