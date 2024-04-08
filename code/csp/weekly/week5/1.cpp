#include<bits/stdc++.h>
using namespace std;

//int 1e+9;
//long 1e+19
int n,m;//n块巨石，m次询问
int l,r;//是否每一个英文字母都至少出现了一次
char character[500000+30];
//string character;
//map<char,int> mp[500000+30];//实现前缀和--MLE
//map<char,int> temp;
int cnum[500030][27]={0};
//set<int> cnum[27];
//vector<vector<int>> mp;
int main(){
    //巨石迷阵
    //n块巨石，每块石头上有大写英文字母
    //前缀和
    cin>>n;
    for(int i=0;i<=26;i++) cnum[0][i]=0;
    for(int i=1;i<=n;i++) //scanf("%c",&character[i]);——很快啊，全WA了。
    {
        cin>>character[i];
        //mp[i]=mp[i-1];//sum[i]=sum[i-1]+a[i];
        //mp[i].insert({character[i],1});
        //mp[i][character[i]]++;
        //cnum[character[i]-'A'+1].insert(i);
        for(int j=1;j<=26;j++) cnum[i][j]=cnum[i-1][j];
        cnum[i][character[i]-'A'+1]=cnum[i-1][character[i]-'A'+1]+1;
    }
    
    //cin>>character;
    cin>>m;
    for(int i=1;i<=m;i++){
        //cin>>l>>r;
        scanf("%d%d",&l,&r);
        //bool sum[26+2]={false};
        int num=0;//记录是否到达26，初始化
        /*
        for(int j=l;j<=r;j++){           
            if(sum[character[j]-'A'+1]==false){
                sum[character[j]-'A'+1]=true;
                num++;
            }
            if(num==26) break;
        }
        }
        */
       /*
        else{
        for(int j=1;j<=26;j++){
            if(cnum[j].empty()) break;
            auto k=cnum[j].lower_bound(l);//>=,为空时bug
            if(k!=cnum[j].end()) num+=((*k)<=r);
        }
        }
        */
        for(int j=1;j<=26;j++){
        //if((cnum[r][j]-cnum[l-1][j])>0)
          //  num++;
          num+=((cnum[r][j]-cnum[l-1][j])>0);
        }
        /*
        temp=mp[r];
        for(auto k=mp[l-1].begin();k!=mp[l-1].end();k++){
            //auto j=temp.find(k->first);不用找一定有
            if(k->second>=temp[k->first]) temp.erase(k->first);
            //<无所谓
        }
        */
        //if(temp.size()==26) cout<<"YES"<<endl;
        //cout<<num;
        if(num==26) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}