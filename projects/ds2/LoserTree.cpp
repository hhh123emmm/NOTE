#include "LoserTree.h"
#include<math.h>
template<class T>
LoserTree<T>::LoserTree(T *thePlayer, int theNumberOfPlayers){
    int n=theNumberOfPlayers;
    player=thePlayer;
    numberOfPlayers=n;
    tree=new int[n+1];
    temp=new int[n+1];
    int s=pow(2,floor(log(n-1)/log(2)));
    lowExt=2*(n-s);
    offset=2*s-1;
    for(int i=2;i<=lowExt;i+=2) play((i+offset)/2,i-1,i);
    int t;
    if(n%2==1){
        play(n/2,temp[n-1],lowExt+1);
        t=lowExt+3;
    }
    else t=lowExt+2;
    for(int i=t;i<=n;i+=2) play((i-lowExt+n-1)/2,i-1,i);
    tree[0]=temp[1];
}

template<class T>
void LoserTree<T>::play(int index,int l,int r){
    //数据较小的晋级
    //if(palyer[l]<player[r]) tree[index]=l;
    tree[index]=loser(l,r);
    //else tree[index]=r;
    temp[index]=winner(l,r);
    while(index%2==1&&index>1)//右节点非根节点？
    {
        //tree[index/2]=(player[tree[index-1]]<=player[tree[index]])?tree[index-1]:tree[index];
        tree[index/2]=loser(temp[index-1],temp[index]);
        temp[index/2]=winner(temp[index-1],temp[index]);
        index/=2;
    }
}

template<class T>
void LoserTree<T>::rePlay(int thePlayer,T newValue){
    int n=numberOfPlayers;
    player[thePlayer]=newValue;
    int mn,lech,rich;
    if(thePlayer<=lowExt){
        mn=(offset+thePlayer)/2;
        lech=2*mn-offset;
        rich=lech+1;
    }
    else {
        mn=(thePlayer-lowExt+n-1)/2;
        if(2*mn==n-1){
            lech=temp[2*mn];
            rich=lech+1;
        }
        else{
            lech=2*mn-n+1+lowExt;
            rich=lech+1;
        }
    }
    if(thePlayer==tree[0]){
        for(;mn>=1;mn/=2){
            int oldone=tree[mn];
            tree[mn]=loser(oldone,thePlayer);
            temp[mn]=winner(oldone,thePlayer);
            thePlayer=temp[mn];
        }
    }
    else {
        tree[mn]=loser(lech,rich);
        temp[mn]=winner(lech,rich);
        if(mn==n-1&&n%2==1){
            mn/=2;
            tree[mn]=loser(temp[n-1],lowExt+1);
            temp[mn]=winner(temp[n-1],lowExt+1);
        }
        mn/=2;
        for(;mn>=1;mn/=2){
            tree[mn]=loser(temp[mn*2],temp[mn*2+1]);
            temp[mn]=winner(temp[mn*2],temp[mn*2+1]);
        }
    }
    tree[0]=temp[1];
}
template<class T>
void LoserTree<T>::initialize(T *thePlayer,int theNumberOfPlayers){
    player=thePlayer;
    numberOfPlayers=theNumberOfPlayers;//选手初始化
    //lowExt,offset,tree
    delete []tree;
    tree=new int[numberOfPlayers];//tree初始化
    //offset-->s=log_2(n-1)
    int i,s;
    for(s=1;2*s<=numberOfPlayers-1;s+=s);
    offset=2*s-1;//最底层最左端的内部节点索引
    //lowExt
    lowExt=2*(numberOfPlayers-s);//最底层外部节点个数，次底层内部节点2倍
    //tree赋值
    /*
    for(i=2;i<=lowExt;i+=2)
        play((offset+i)/2,i-1,i);
    if(n%2==1)
    {
        play(n/2,tree[n-1],lowExt+1);
        i=lowExt+3;//倒数第二层外部节点的右儿子
    }
    else i=lowExt+2;
    for(;i<=n;i+=2) play((i-lowExt+n-1)/2,i-1,i);
    //tree此时是赢者树，调整为输者树
    tree[0]=tree[1];//1~n-1
    for(int j=1;j<=n-1;j++){
        if(2*j+1<=n-1)
        tree[j]=tree[j]==tree[2*j]?tree[2*j+1]:tree[2*j];
        else 
    }
    */
    //
}
