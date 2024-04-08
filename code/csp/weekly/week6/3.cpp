#include<bits/stdc++.h>
using namespace std;

//并查集！
const int MAX=1e5;
int n,m;
int l,r;
struct unionfindnode
{
    int parent;//孩子数/root
    bool root;
    unionfindnode(){parent=1;root=true;}
};
unionfindnode uf[MAX+30];
int main(){
    cin>>n>>m;//n m
    //n:1-n村庄
    if(n!=0) n--;//n个村庄最少n-1
    for(int i=1;i<=m;i++){
        cin>>l>>r;
        if(l==r) cout<<n<<endl;
        else{
            if(uf[l].root==true&&uf[r].root==true){
                if(n!=0) n--;
                if(uf[l].parent>uf[r].parent){
                    uf[l].parent+=uf[r].parent;
                    uf[r].root=false;
                    uf[r].parent=l;
                }
                else{
                    uf[r].parent+=uf[l].parent;
                    uf[l].root=false;
                    uf[l].parent=r;
                }
            }
            else{
                int u=l,v=r;
                if(uf[u].root==false){
                    while(!uf[u].root) u=uf[u].parent;
                }
                if(uf[v].root==false){
                    while(!uf[v].root) v=uf[v].parent;
                }
                if(u==v);
                else {
                    if(n!=0) n--;
                    if(uf[u].parent>uf[v].parent){
                    uf[u].parent+=uf[v].parent;
                    uf[v].root=false;
                    uf[v].parent=l;
                }
                else{
                    uf[v].parent+=uf[u].parent;
                    uf[u].root=false;
                    uf[u].parent=v;
                }
                }
            }
            cout<<n<<endl;
        }
    }
}