#include "LoserTree.h"

template<class T>
void LoserTree<T>::play(int index,int l,int r){
    //数据较小的晋级
    if(palyer[l]<player[r]) tree[index]=l;
    else tree[index]=r;
    while(index%2==1&&p>1)//右节点非根节点？
    {
        tree[index/2]=(player[tree[index-1]]<=player[tree[index]])?tree[index-1]:tree[index];
        index/=2;
    }
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
    
}