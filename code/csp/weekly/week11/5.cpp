#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+30;

int m,pp;
int p,v;
int d[maxn<<2],a[maxn];

void build(int x,int l,int r){
    if(l==r){
        d[x]=a[l];
        return;
    }
    int m=(l+r)/2;
    build(x*2,l,m);
    build(x*2+1,m+1,r);
    d[x]=d[x*2]+d[x*2+1];
}

void upd(int x,int l,int r){
    if(l==r){
        d[x]+=v;
        return;
    }
    int m=(l+r)/2;
    if(p<=m) upd(x*2,l,m);
    else upd(x*2+1,m+1,r);
    d[x]=d[x*2]+d[x*2+1];
}

int ask(int x,int l,int r,int p1,int p2){
    //p1,p2
    if(l==p1&&r==p2) return d[x];
    int m=(l+r)/2;
    if(p2<=m) return ask(x*2,l,m,p1,p2);
    else if(p1>m) return ask(x*2+1,m+1,r,p1,p2);
    else{
        int lch_val=ask(x*2,l,m,p1,m);
        int rch_val=ask(x*2+1,m+1,r,m+1,p2);
        return lch_val+rch_val;
    }
}

int main(){
    cin>>m>>pp;
    int temp,cnt=0;
    for(int i=1;i<=m;i++){
        char c;int t;
        scanf("%c%d",&c,&t);
        if(c=='Q'){
            temp=ask(cnt-t,cnt,0,0,n);
            printf("%d\n",a);
        }else{
            upf(cnt++,(t+a)%pp);
        }
    }
}