//8
//bfs
//map

#include<bits/stdc++.h>
using namespace std;
string source="12348765",destination,temp;

void arrange1(){
    //横向对调0 1 2 3-4 5 6 7
    if(source.size()!=8) return;
    for(int i=0;i<4;i++) swap(source[0+i],source[4+i]);
    cout<<" 1 "<<source<<endl;
}

map<string,string> mp;
queue<string> q;
void arrange2(){//3/7--0/4  0/4--1/5 1/5--2/6 2/6--4/7
    if(source.size()!=8) return;
    swap(source[3],source[0]);swap(source[7],source[4]);
    swap(source[3],source[2]);swap(source[7],source[6]);
    swap(source[1],source[2]);swap(source[5],source[6]);
    cout<<" 2s "<<source<<endl;
}

void reverse2(){
    if(source.size()!=8) return;
    swap(source[1],source[2]);swap(source[5],source[6]);
    swap(source[3],source[2]);swap(source[7],source[6]);
    swap(source[3],source[0]);swap(source[7],source[4]);
    cout<<" 2r "<<source<<endl;
}

void arrange3(){//1/2/5/6--2/6/1/5
    if(source.size()!=8) return;
    swap(source[1],source[2]);
    swap(source[5],source[6]);
    swap(source[1],source[6]);
    cout<<" 3s "<<source<<endl;
}

void reverse3(){
    if(source.size()!=8) return;
    swap(source[1],source[6]);
    swap(source[5],source[6]);
    swap(source[1],source[2]);
    cout<<" 3r "<<source<<endl;
}

void BFS(){
    q.push(source);
    string begin=source;
    while(!q.empty()){
        source=q.front();
        temp=source;
        q.pop();
        arrange1();
        if(source!=begin&&mp.find(source)==mp.end()){
            //该状态第一次出现
            mp[source]=mp[temp];
            mp[source].push_back('A');
            q.push(source);
            if(source==destination) return;
        }
        arrange1();
        arrange2();
        if(source!=begin&&mp.find(source)==mp.end()){
            //该状态第一次出现
            mp[source]=mp[temp];
            mp[source].push_back('B');
            q.push(source);
            if(source==destination) return;
        } 
        reverse2();
        arrange3();
        if(source!=begin&&mp.find(source)==mp.end()){
            //该状态第一次出现
            mp[source]=mp[temp];
            mp[source].push_back('C');
            q.push(source);
            if(source==destination) return;
        } 
    }

}

int main(){
    char te;
    for(int i=1;i<=8;i++){
        cin>>te;
        destination.push_back(te);
    }
    cout<<destination<<" di"<<endl;
    swap(destination[4],destination[7]);
    swap(destination[5],destination[6]);
    cout<<destination<<" do"<<endl;
    BFS();
    cout<<mp[destination].size()<<endl<<mp[destination]<<endl;
    return 0;
}