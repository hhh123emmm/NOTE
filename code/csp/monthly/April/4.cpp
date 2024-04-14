#include<bits/stdc++.h>
using namespace std;
const int MAX_SIZE=100+30;
int n,m,p,q;

//节点
int vit[MAX_SIZE][MAX_SIZE][2];//左岸的羊-狼-人

struct Node{
    int s,f,c;
};

int main(){
    int T;cin>>T;
    while(T--){
        cin>>n>>m>>p>>q;
        for(int i=0;i<MAX_SIZE;i++){
            for(int j=0;j<MAX_SIZE;j++){
                vit[i][j][0]=0;
                vit[i][j][1]=0;
            }
        }
        Node init={n,m,1};
        queue<pair<Node,int>> que;
        que.push({init,0});
        vit[init.s][init.f][init.s]=1;
        bool win=false;
        while(!que.empty()){
            Node now=que.front().first;
            int step=que.front().second;
            que.pop();

            if(now.s==0){
                win=true;
                cout<<step<<'\n';
            }
            //转移
            for(int i=0;i<=p;i++){//上船的羊数
                for(int j=0;j<=p;j++){
                    //上船的狼数
                    if(i+j>p) continue;
                    int space=p-i-j;

                    //==>
                    if(now.c==1){
                        //左岸有人
                        Node node={now.s-i,now.f-j,0};
                        //确保安全
                        if(node.s<0||node.f<0) continue;
                        if(node.f>node.s+q and node.s!=0) continue;
                        else{
                            if(vit[node.s][node.f][node.c]==0){
                                que.push({node,step+1});
                                vit[node.s][node.f][node.c]=1;
                            }
                        }
                    }else{
                        //没人
                        Node node={now.s+i,now.f+j,1};
                        //确保安全
                        if(node.s<0||node.f<0) continue;
                        if(node.f>node.s+q and node.s!=0) continue;
                        else{
                            if(vit[node.s][node.f][node.c]==0){
                                que.push({node,step+1});
                                vit[node.s][node.f][node.c]=1;
                            }
                        }
                    }
                }
            }
            //访问过所有节点，无答案
            if(win==false)
            cout<<"-1"<<'\n';
        }
    }
}